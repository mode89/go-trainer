#ifndef __GNUGO_PLAYER_BASE_H__
#define __GNUGO_PLAYER_BASE_H__

#include "go/player.h"
#include <memory>

namespace gnugo {

    class Engine;

    class PlayerBase : public go::IPlayer
    {
    public:
        virtual void
        Init( go::Color, unsigned boardSize );

    public:
        PlayerBase( Engine & );
        ~PlayerBase();

    protected:
        Engine &    mEngine;
        go::Color   mColor;
    };

} // namespace gnugo

#endif // __GNUGO_PLAYER_BASE_H__
