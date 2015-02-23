#ifndef __GNUGO_PLAYER_H__
#define __GNUGO_PLAYER_H__

#include "gnugo/player_base.h"

namespace gnugo {

    class Player : public PlayerBase
    {
    public:
        go::Move
        MakeMove( const go::Board & );

    public:
        Player( Engine & );
        ~Player();
    };

} // namespace gnugo

#endif // __GNUGO_PLAYER_H__
