#ifndef __GA_SOLVER_INL__
#define __GA_SOLVER_INL__

#include <stddef.h>

namespace GA {

    template < class Phenotype >
    Solver< Phenotype >::Solver( size_t populationSize )
        : mPopulationSize( populationSize )
    {}

    template < class Phenotype >
    Solver< Phenotype >::~Solver()
    {}

    template < class Phenotype >
    double Solver< Phenotype >::Step()
    {
        // Generate initial population

            if ( mPopulation.empty() )
            {
                mPopulation.resize( mPopulationSize );
                for ( auto & it : mPopulation )
                {
                    it.first = this->CreateIndividual();
                    it.second = FLT_MAX;
                }
            }

        // Selection

            Population selection( static_cast< size_t >( sqrt( static_cast< double >( mPopulationSize ) ) ) );

            // Calculate fitness
            #pragma omp parallel
            #pragma omp for
            for ( int i = 0; i < static_cast< int >( mPopulationSize ); ++ i )
            {
                double fitness = Fitness( mPopulation[i].first );
                mPopulation[i].second = fitness;
            }

            // Sort according to the fitness values
            std::sort( mPopulation.begin(), mPopulation.end(),
                [] ( const PairPhenotypeFitness & p1, const PairPhenotypeFitness & p2 ) -> bool {
                    return p1.second < p2.second;
                } );
            mFittest = mPopulation[0];

            std::copy_n( mPopulation.begin(), selection.size(), selection.begin() );

        // Crossover

            std::uniform_int_distribution<> distr( 0, selection.size() - 1 );
            for ( size_t i = 1; i < mPopulationSize; ++ i )
            {
                PairPhenotypeFitness child;
                PairPhenotypeFitness & p1 = selection[ distr( mRandomEngine ) ];
                PairPhenotypeFitness & p2 = selection[ distr( mRandomEngine ) ];
                child.first = Crossover( p1.first, p2.first );
                mPopulation[i] = child;
            }

        // Mutation

            for ( size_t i = 1; i < mPopulationSize; ++ i )
            {
                PairPhenotypeFitness mutant;
                mutant.first = Mutation( mPopulation[i].first );
                mPopulation[i] = mutant;
            }

        return mFittest.second;
    }

} // namespace GA

#endif // __GA_SOLVER_INL__
