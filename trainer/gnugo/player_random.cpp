#include "gnugo/engine.h"
#include "gnugo/player_random.h"
#include "go/board.h"

namespace gnugo {

    using namespace go;

    PlayerRandom::PlayerRandom( Engine & engine, int seed /* = 0 */ )
        : PlayerBase( engine )
        , mRandomEngine( seed )
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
        } while ( !mEngine.IsLegal( mColor, retval ) );
        mEngine.Play( mColor, retval );

        return retval;
    }

} // namespace gnugo
