#ifndef __GNUGO_GAME_H__
#define __GNUGO_GAME_H__

#include "go/game.h"

namespace gnugo {

    class Engine;
    class PlayerBase;

    class Game : public go::Game
    {
    public:
        Game( unsigned boardSize, PlayerBase & black, PlayerBase & white, Engine & );
        ~Game();

    protected:
        virtual void
        Init();

        virtual void
        UpdateBoard( go::Color lastPlayer, go::Move lastMove );

    protected:
        Engine &    mEngine;
    };

} // namespace gnugo

#endif // __GNUGO_GAME_H__
