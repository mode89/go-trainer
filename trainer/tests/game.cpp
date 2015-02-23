#include "cmn/platform.h"

CMN_WARNING_PUSH
CMN_WARNING_DISABLE_MSVC( 4625 4626 )
#include "gtest/gtest.h"
CMN_WARNING_POP

#include "gnugo/engine.h"
#include "gnugo/game.h"
#include "gnugo/player.h"
#include "gnugo/player_random.h"

TEST( LearningService, Game )
{
    const unsigned kBoardSize = 9;
    const unsigned kLevel     = 1;

    gnugo::Engine engine( kLevel, kBoardSize );
    gnugo::Player blackPlayer( engine );
    gnugo::Player whitePlayer( engine );
    gnugo::Game game( kBoardSize, blackPlayer, whitePlayer, engine );

    game.Play();
}

TEST( LearningService, PlayerRandom )
{
    const unsigned kBoardSize = 9;
    const unsigned kLevel     = 1;

    gnugo::Engine engine( kLevel, kBoardSize );
    gnugo::PlayerRandom blackPlayer( engine );
    gnugo::Player whitePlayer( engine );
    gnugo::Game game( kBoardSize, blackPlayer, whitePlayer, engine );

    game.Play();
}
