#include "go/board.h"
#include "go/player_random.h"

namespace go {

    PlayerRandom::PlayerRandom()
        : mRandomEngine()
    {
    }

    PlayerRandom::~PlayerRandom()
    {
    }

    Move PlayerRandom::MakeMove( const Board & board )
    {
        unsigned cellCount = board.GetSize() * board.GetSize();

        std::discrete_distribution< unsigned > distType( { 1.0, 1.0 / cellCount } );
        std::uniform_int_distribution< unsigned > distCoord( 0, board.GetSize() - 1 );

        Move retval;
        do {
            retval.type     = ( distType( mRandomEngine ) == 0 ) ? MOVE_TYPE_PLACE : MOVE_TYPE_PASS;
            retval.row      = distCoord( mRandomEngine );
            retval.column   = distCoord( mRandomEngine );
        } while ( !( retval.type == MOVE_TYPE_PASS || board( retval.row, retval.column ) == CELL_EMPTY ) );

        return retval;
    }

} // namespace go
