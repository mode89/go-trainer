#include "gnugo/player.h"
#include "gnugo/engine.h"

namespace gnugo {

    using namespace go;

    Player::Player( Engine & engine )
        : PlayerBase( engine )
    {
    }

    Player::~Player()
    {
    }

    Move Player::MakeMove( const Board & board )
    {
        return mEngine.Genmove( mColor );
    }

} // namespace gnugo
