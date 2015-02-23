#include "gnugo/engine.h"
#include "gnugo/game.h"
#include "gnugo/player_base.h"

namespace gnugo {

    Game::Game( unsigned boardSize, PlayerBase & black, PlayerBase & white, Engine & engine )
        : go::Game( boardSize, black, white )
        , mEngine( engine )
    {
    }

    Game::~Game()
    {
    }

    void Game::Init()
    {
        mEngine.ClearBoard();
    }

    void Game::UpdateBoard( go::Color lastPlayer, go::Move lastMove )
    {
        mEngine.UpdateBoard( mBoard );
    }

} // namespace gnugo
