#ifndef __GA_SOLVER_H__
#define __GA_SOLVER_H__

#include "cmn/shared_ptr_typedefs.h"

#include <float.h>

#include <algorithm>
#include <memory>
#include <random>
#include <vector>

namespace GA {

    template < typename Phenotype >
    class Solver
    {
    private:
        typedef std::pair< Phenotype, double > PairPhenotypeFitness;
        typedef std::vector< PairPhenotypeFitness > Population;

    public:
        double Step()
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

            // Iterating

            Population selection( static_cast< size_t >( sqrt( static_cast< double >( mPopulationSize ) ) ) );

            // Selection
            {
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
            }

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

        Phenotype GetFittest() const { return mFittest.first; }

    public:
        Solver( size_t populationSize )
            : mPopulationSize( populationSize )
        {}

        virtual ~Solver()
        {}

    protected:
        virtual Phenotype
        CreateIndividual() = 0;

        virtual double
        Fitness( const Phenotype & ) = 0;

        virtual Phenotype
        Crossover( const Phenotype &, const Phenotype & ) = 0;

        virtual Phenotype
        Mutation( const Phenotype & ) = 0;

    protected:
        typedef std::default_random_engine RandomEngine;

        RandomEngine            mRandomEngine;
        size_t                  mPopulationSize;
        Population              mPopulation;
        PairPhenotypeFitness    mFittest;
    };

} // namespace GA

#endif // __GA_SOLVER_H__
