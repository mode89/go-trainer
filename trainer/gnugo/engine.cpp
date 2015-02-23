#include "cmn/trace.h"
#include "gnugo/engine.h"
#include "go/board.h"

namespace gnugo {

    inline static const char * ColorToString( go::Color color )
    {
        switch ( color )
        {
        case go::COLOR_BLACK:
            return "black";
        case go::COLOR_WHITE:
            return "white";
        default:
            CMN_FAIL();
            return nullptr;
        }
    }

    inline static std::string CoordToString( unsigned row, unsigned column )
    {
        char rowChar = row + 'A';
        std::string retval;
        retval.push_back( ( rowChar >= 'I' ) ? ( rowChar + 1 ) : rowChar );
        retval += std::to_string( column + 1 );
        return retval;
    }

    inline static void StringToCoord( const char * str, unsigned & row, unsigned & column )
    {
        char rowChar = str[0];
        row     = ( rowChar > 'I' ) ? ( rowChar - 'A' - 1 ) : ( rowChar - 'A' );
        column  = std::atoi( str + 1 ) - 1;
    }

    Engine::Engine( unsigned level, unsigned boardSize, unsigned seed /* = 0 */ )
        : mLevel( level )
        , mBoardSize( boardSize )
        , mStdoutRead( nullptr )
        , mStdoutWrite( nullptr )
        , mStdinRead( nullptr )
        , mStdinWrite( nullptr )
    {
        SECURITY_ATTRIBUTES securityAttributes;
        ZeroMemory( &securityAttributes, sizeof( SECURITY_ATTRIBUTES ) );
        securityAttributes.nLength          = sizeof( SECURITY_ATTRIBUTES );
        securityAttributes.bInheritHandle   = TRUE;

        BOOL success = FALSE;
        success = CreatePipe( &mStdoutRead, &mStdoutWrite, &securityAttributes, 0 );
        CMN_ASSERT( success != FALSE );
        success = SetHandleInformation( mStdoutRead, HANDLE_FLAG_INHERIT, 0 );
        CMN_ASSERT( success != FALSE );

        success = CreatePipe( &mStdinRead, &mStdinWrite, &securityAttributes, 0 );
        CMN_ASSERT( success != FALSE );
        success = SetHandleInformation( mStdinWrite, HANDLE_FLAG_INHERIT, 0 );
        CMN_ASSERT( success != FALSE );

        PROCESS_INFORMATION processInformation;
        ZeroMemory( &processInformation, sizeof( PROCESS_INFORMATION ) );

        STARTUPINFO startupInfo;
        ZeroMemory( &startupInfo, sizeof( STARTUPINFO ) );
        startupInfo.cb          = sizeof( STARTUPINFO );
        startupInfo.hStdError   = mStdoutWrite;
        startupInfo.hStdOutput  = mStdoutWrite;
        startupInfo.hStdInput   = mStdinRead;
        startupInfo.dwFlags     = STARTF_USESTDHANDLES;

        std::string cmdLine =
            std::string( GNUGO_EXE ) +
            std::string( " --mode gtp" ) +
            std::string( " --level " ) + std::to_string( mLevel ) +
            std::string( " --boardsize " ) + std::to_string( mBoardSize ) +
            ( seed ? ( std::string( " --seed " ) + std::to_string( seed ) ) : "" ) +
            std::string( " --never-resign" );

        success = CreateProcess( NULL, const_cast< char * >( cmdLine.data() ), NULL, NULL,
            TRUE, 0, NULL, NULL, &startupInfo, &processInformation );
        CMN_ASSERT( success != FALSE );

        success = CloseHandle( processInformation.hProcess );
        CMN_ASSERT( success != FALSE );
        success = CloseHandle( processInformation.hThread );
        CMN_ASSERT( success != FALSE );
    }

    Engine::~Engine()
    {
        BOOL success = FALSE;
        success = CloseHandle( mStdoutRead );
        CMN_ASSERT( success );
        success = CloseHandle( mStdoutWrite );
        CMN_ASSERT( success );
        success = CloseHandle( mStdinRead );
        CMN_ASSERT( success );
        success = CloseHandle( mStdinWrite );
        CMN_ASSERT( success );
    }

    std::string Engine::Execute( std::string command )
    {
        command += '\n';

        DWORD writtenBytes = 0;
        BOOL success = FALSE; CMN_UNUSED( success );
        success = WriteFile( mStdinWrite, command.c_str(), command.size(), &writtenBytes, 0 );
        CMN_ASSERT( success != FALSE );

        std::string response;
        int newLineCount = 0;
        while ( newLineCount < 2 )
        {
            char newChar;
            DWORD readBytes;
            success = ReadFile( mStdoutRead, &newChar, 1, &readBytes, 0 );
            CMN_ASSERT( success != FALSE );
            CMN_ASSERT( readBytes != 0 );

            if ( newChar != '\r' && newChar != '\n' )
                response.push_back( newChar );
            else if ( newChar == '\n' )
                newLineCount ++;
        }

        return response;
    }

    void Engine::ClearBoard()
    {
        std::string response = Execute( "clear_board" );
        CMN_ASSERT( response[0] == '=' );
    }

    bool Engine::Play( go::Color color, go::Move move )
    {
        std::string command =
            std::string( "play " ) +
            ColorToString( color ) +
            std::string( " " );

        switch ( move.type )
        {
        case go::MOVE_TYPE_PLACE:
            command += CoordToString( move.row, move.column );
            break;
        case go::MOVE_TYPE_PASS:
            command += "pass";
            break;
        default:
            CMN_FAIL();
        }

        std::string response = Execute( command );
        return response[0] == '=';
    }

    go::Move Engine::Genmove( go::Color color )
    {
        std::string command =
            std::string( "genmove " ) +
            ColorToString( color );

        std::string response = Execute( command );
        CMN_ASSERT( response[0] == '=' );

        go::Move retval;

        if ( std::string( "PASS" ) == ( response.data() + 2 ) )
        {
            retval.type = go::MOVE_TYPE_PASS;
        }
        else
        {
            retval.type = go::MOVE_TYPE_PLACE;
            StringToCoord( response.data() + 2, retval.row, retval.column );
        }

        return retval;
    }

    void Engine::ListStones( std::list< go::Stone > & stones, go::Color color )
    {
        std::string command =
            std::string( "list_stones " ) +
            ColorToString( color );

        std::string response = Execute( command );
        CMN_ASSERT( response[0] == '=' );

        char * token = std::strtok( const_cast< char * >( response.data() + 2 ), " " );
        while ( token != NULL )
        {
            go::Stone stone;
            stone.color = color;
            StringToCoord( token, stone.row, stone.column );
            stones.push_back( stone );

            token = std::strtok( NULL, " " );
        }
    }

    void Engine::ListStones( std::list< go::Stone > & stones )
    {
        ListStones( stones, go::COLOR_BLACK );
        ListStones( stones, go::COLOR_WHITE );
    }

    void Engine::UpdateBoard( go::Board & board )
    {
        board.Clear();

        std::list< go::Stone > stones;
        ListStones( stones );

        for ( auto & stone : stones )
        {
            switch ( stone.color )
            {
            case go::COLOR_BLACK:
                board( stone.row, stone.column ) = go::CELL_BLACK;
                break;
            case go::COLOR_WHITE:
                board( stone.row, stone.column ) = go::CELL_WHITE;
                break;
            default:
                CMN_FAIL();
            }
        }
    }

    float Engine::GetScore( go::Color color )
    {
        std::string response = Execute( "final_score" );
        CMN_ASSERT( response[0] == '=' );

        float score = std::atof( response.c_str() + 4 );
        if ( ( response[2] == 'W' && color == go::COLOR_WHITE ) ||
             ( response[2] == 'B' && color == go::COLOR_BLACK ) )
            return score;
        else
            return -score;
    }

} // namespace gnugo
