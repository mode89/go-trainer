#include "cmn/trace.h"
#include "gnugo/engine.h"
#include "go/board.h"

#include <cstring>

#if CMN_LINUX
    #include <stdio.h>
    #include <unistd.h>

    #define PARENT_WRITE_PIPE   0
    #define PARENT_READ_PIPE    1

    #define READ_FD     0
    #define WRITE_FD    1

    #define PARENT_READ_FD  ( mPipes[ PARENT_READ_PIPE ][ READ_FD ] )
    #define PARENT_WRITE_FD ( mPipes[ PARENT_WRITE_PIPE ][ WRITE_FD ] )
    #define CHILD_READ_FD   ( mPipes[ PARENT_WRITE_PIPE ][ READ_FD ] )
    #define CHILD_WRITE_FD  ( mPipes[ PARENT_READ_PIPE ][ WRITE_FD ] )
#endif // CMN_LINUX

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
#if CMN_WIN32
        , mStdoutRead( nullptr )
        , mStdoutWrite( nullptr )
        , mStdinRead( nullptr )
        , mStdinWrite( nullptr )
#endif
    {
        std::string cmdLine =
            std::string( " --mode gtp" ) +
            std::string( " --level " ) + std::to_string( mLevel ) +
            std::string( " --boardsize " ) + std::to_string( mBoardSize ) +
            ( seed ? ( std::string( " --seed " ) + std::to_string( seed ) ) : "" ) +
            std::string( " --never-resign" );

#if CMN_WIN32
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

        success = CreateProcess( GNUGO_EXE, const_cast< char * >( cmdLine.data() ), NULL, NULL,
            TRUE, 0, NULL, NULL, &startupInfo, &processInformation );
        CMN_ASSERT( success != FALSE );

        success = CloseHandle( processInformation.hProcess );
        CMN_ASSERT( success != FALSE );
        success = CloseHandle( processInformation.hThread );
        CMN_ASSERT( success != FALSE );
#elif CMN_LINUX
        pipe( mPipes[ PARENT_READ_PIPE ] );
        pipe( mPipes[ PARENT_WRITE_PIPE ] );

        if ( fork() == 0 )
        {
            dup2( CHILD_READ_FD, STDIN_FILENO );
            dup2( CHILD_WRITE_FD, STDOUT_FILENO );

            close( CHILD_READ_FD );
            close( CHILD_WRITE_FD );
            close( PARENT_READ_FD );
            close( PARENT_WRITE_FD );

            execl( GNUGO_EXE, cmdLine.c_str() );
            exit( 0 );
        }
        else
        {
            close( CHILD_READ_FD );
            close( CHILD_WRITE_FD );
        }
#else
    #error Unsupported platform
#endif
    }

    Engine::~Engine()
    {
        Quit();

#if CMN_WIN32
        BOOL success = FALSE;
        success = CloseHandle( mStdoutRead );
        CMN_ASSERT( success );
        success = CloseHandle( mStdoutWrite );
        CMN_ASSERT( success );
        success = CloseHandle( mStdinRead );
        CMN_ASSERT( success );
        success = CloseHandle( mStdinWrite );
        CMN_ASSERT( success );
#elif CMN_LINUX
        close( PARENT_READ_FD );
        close( PARENT_WRITE_FD );
#endif // CMN_WIN32
    }

#if CMN_WIN32
    #define WRITE( buffer, size ) \
        { \
            DWORD writtenBytes = 0; \
            BOOL success = FALSE; CMN_UNUSED( success ); \
            success = WriteFile( mStdinWrite, buffer, size, &writtenBytes, 0 ); \
            CMN_ASSERT( success != FALSE ); \
        }
    #define READ( buffer, size, readBytes ) \
        { \
            BOOL success = FALSE; CMN_UNUSED( success ); \
            DWORD dwReadBytes; \
            success = ReadFile( mStdoutRead, buffer, size, &dwReadBytes, 0 ); \
            CMN_ASSERT( success != FALSE ); \
            readBytes = dwReadBytes; \
        }
#elif CMN_LINUX
    #define WRITE( buffer, size ) \
        write( PARENT_WRITE_FD, buffer, size )
    #define READ( buffer, size, readBytes ) \
        readBytes = read( PARENT_READ_FD, buffer, size )
#endif

    std::string Engine::Execute( std::string command )
    {
        command += '\n';

        WRITE( command.c_str(), command.size() );

        std::string response;
        int newLineCount = 0;
        while ( newLineCount < 2 )
        {
            char newChar;
            int readBytes = 0;
            READ( &newChar, 1, readBytes );
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

    void Engine::Quit()
    {
        std::string response = Execute( "quit" );
        CMN_ASSERT( response[0] == '=' );
    }

} // namespace gnugo
