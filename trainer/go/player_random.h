#ifndef __GO_PLAYER_RANDOM_H__
#define __GO_PLAYER_RANDOM_H__

#include "go/player.h"
#include <random>

namespace go {

    class PlayerRandom : public IPlayer
    {
    public:
        void
        SetColor( Color );

        Move
        MakeMove( const Board & );

    public:
        PlayerRandom();
        ~PlayerRandom();

    private:
        std::default_random_engine  mRandomEngine;
    };

} // namespace go

#endif // __GO_PLAYER_RANDOM_H__
