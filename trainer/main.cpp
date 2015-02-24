#include "cmn/trace.h"
#include "gnugo/engine.h"
#include "gnugo/game.h"
#include "gnugo/player.h"
#include "gnugo/player_ann.h"
#include "gnugo/player_random.h"

#include <fstream>

const unsigned kBoardSize       = 9;
const unsigned kCellCount       = kBoardSize * kBoardSize;
const unsigned kPopulationSize  = 10;
const unsigned kGameCount       = 50;

double FitnessOp( ANN::ConstPerceptronIn nw )
{
    double fitness = 0.0;

    #pragma omp parallel
    #pragma omp for
    for ( int i = 0; i < kGameCount; ++ i )
    {
        gnugo::Engine       engine( 1, kBoardSize );
        gnugo::PlayerAnn    blackPlayer( nw, engine );
        gnugo::Player       whitePlayer( engine );
        gnugo::Game         game( kBoardSize, blackPlayer, whitePlayer, engine );
        game.Play();

        fitness += engine.GetScore( go::COLOR_WHITE );
    }

    return fitness / kGameCount;
}

int main( int argc, char * argv[] )
{
    ANN::IPerceptronGeneticAlgorithmTrainerRef trainer =
        ANN::CreatePerceptronGeneticAlgorithmTrainer( FitnessOp, kCellCount, kCellCount + 1, kPopulationSize );
    trainer->SetMutationProbability( 0.001f );
    trainer->SetMutationSpeed( 0.3f );

    double fitness = 0.0;
    do {
        fitness = trainer->Step();
        CMN_MSG( "%3.3f", fitness );

        std::ofstream fittestOutputStream( "fittest.nw", std::ios::out | std::ios::trunc );
        boost::archive::binary_oarchive fittestOutputArchive( fittestOutputStream );
        fittestOutputArchive << *trainer->GetFittest();
    } while ( fitness > -70.0 );
}
