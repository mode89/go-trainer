#include "cmn/trace.h"
#include "go/game.h"

namespace go {

    Game::Game( unsigned boardSize, IPlayer & blackPlayer, IPlayer & whitePlayer )
        : mBoard( boardSize )
    {
        mPlayer[0] = &blackPlayer;
        mPlayer[1] = &whitePlayer;
    }

    Game::~Game()
    {
    }

    void Game::Play()
    {
        Init();

        mPlayer[0]->Init( COLOR_BLACK, mBoard.GetSize() );
        mPlayer[1]->Init( COLOR_WHITE, mBoard.GetSize() );

        Move prevMove;
        Move nextMove;

        unsigned moveCount = 0;
        while( true )
        {
            Color color = static_cast< Color >( moveCount & 1 );

            prevMove = nextMove;
            nextMove = mPlayer[ color ]->MakeMove( mBoard );
            moveCount++;

            if ( moveCount > 1 &&
                 prevMove.type == MOVE_TYPE_PASS &&
                 nextMove.type == MOVE_TYPE_PASS )
            {
                break;
            }

            UpdateBoard( color, nextMove );
        }
    }

} // namespace go
