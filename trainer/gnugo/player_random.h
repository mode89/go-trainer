#ifndef __GNUGO_PLAYER_RANDOM_H__
#define __GNUGO_PLAYER_RANDOM_H__

#include "gnugo/player_base.h"
#include <random>

namespace gnugo {

    class PlayerRandom : public PlayerBase
    {
    public:
        go::Move
        MakeMove( const go::Board & );

    public:
        PlayerRandom( Engine &, int seed = 0 );
        ~PlayerRandom();

    private:
        std::default_random_engine  mRandomEngine;
    };

} // namespace gnugo

#endif // __GNUGO_PLAYER_RANDOM_H__
