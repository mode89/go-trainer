#include "cmn/trace.h"
#include "gnugo/engine.h"
#include "gnugo/game.h"
#include "gnugo/player.h"
#include "gnugo/player_ann.h"
#include "gnugo/player_random.h"
#include "opennn/mathematical_model.h"
#include "opennn/neural_network.h"
#include "opennn/performance_functional.h"
#include "opennn/training_strategy.h"

#include <fstream>

using namespace OpenNN;

const unsigned kBoardSize       = 9;
const unsigned kCellCount       = kBoardSize * kBoardSize;
const unsigned kPopulationSize  = 10;
const unsigned kGameCount       = 25;

class Objective : public PerformanceTerm
{
public:
    double calculate_performance( const Vector<double> & params ) const
    {
        NeuralNetwork nw( *neural_network_pointer );
        nw.set_parameters( params );

        double score = 0.0;

        #pragma omp parallel
        #pragma omp for
        for ( int i = 0; i < kGameCount; ++ i )
        {
            gnugo::Engine       engine( 1, kBoardSize );
            gnugo::PlayerAnn    blackPlayer( nw, engine );
            gnugo::Player       whitePlayer( engine );
            gnugo::Game         game( kBoardSize, blackPlayer, whitePlayer, engine );
            game.Play();

            score += engine.GetScore( go::COLOR_WHITE );
        }

        return score / kGameCount;
    }

    double calculate_performance() const
    {
        return 0.0;
    }
};

int main( int argc, char * argv[] )
{
    NeuralNetwork nw( kCellCount, kCellCount, kCellCount + 1 );

    Objective objective;
    objective.set_neural_network_pointer( &nw );

    PerformanceFunctional pf( &nw );
    pf.set_objective_type( PerformanceFunctional::USER_OBJECTIVE );
    pf.set_user_objective_pointer( &objective );

    TrainingStrategy trainingStrategy( &pf );
    trainingStrategy.set_initialization_type( TrainingStrategy::EVOLUTIONARY_ALGORITHM );
    trainingStrategy.set_main_type( TrainingStrategy::NO_MAIN );

    EvolutionaryAlgorithm * evolutionaryAlgorithm = trainingStrategy.get_evolutionary_algorithm_pointer();
    evolutionaryAlgorithm->set_population_size( kPopulationSize );
    evolutionaryAlgorithm->set_display_period( 1 );

    trainingStrategy.perform_training();
}
