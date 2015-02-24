#include "cmn/platform.h"

CMN_WARNING_PUSH
CMN_WARNING_DISABLE_MSVC( 4625 4626 )
#include "gtest/gtest.h"
CMN_WARNING_POP

#include "gnugo/engine.h"
#include "gnugo/game.h"
#include "gnugo/player_ann.h"
#include "gnugo/player_random.h"

double FitnessOp( ANN::ConstPerceptronIn nw )
{
    const unsigned kBoardSize = 9;
    const unsigned kGameCount = 3;

    double fitness = 0.0;

    for ( unsigned i = 0; i < kGameCount; ++ i )
    {
        gnugo::Engine       engine( 1, kBoardSize );
        gnugo::PlayerAnn    blackPlayer( nw, engine );
        gnugo::PlayerRandom whitePlayer( engine, i );
        gnugo::Game         game( kBoardSize, blackPlayer, whitePlayer, engine );

        game.Play();

        fitness += engine.GetScore( go::COLOR_WHITE );
    }

    return fitness / kGameCount;
}

TEST( LS, TrainingIteration )
{
    ANN::IPerceptronGeneticAlgorithmTrainerRef trainer =
        ANN::CreatePerceptronGeneticAlgorithmTrainer( FitnessOp, 81, 82, 3 );
    trainer->Step();
}
