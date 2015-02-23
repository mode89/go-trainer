#ifndef __GO_GAME_H__
#define __GO_GAME_H__

#include "board.h"
#include "player.h"

namespace go {

    class Game
    {
    public:
        void
        Play();

    public:
        Game( unsigned boardSize, IPlayer & black, IPlayer & white );
        ~Game();

    protected:
        virtual void
        Init() = 0;

        virtual void
        UpdateBoard( Color lastPlayer, Move lastMove ) = 0;

    protected:
        IPlayer *   mPlayer[2];
        Board       mBoard;
    };

} // namespace go

#endif // __GO_GAME_H__
