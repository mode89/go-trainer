#ifndef __GA_SOLVER_H__
#define __GA_SOLVER_H__

#include "cmn/shared_ptr_typedefs.h"

#include <float.h>

#include <algorithm>
#include <memory>
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

            size_t selectionCount = static_cast< size_t >( sqrt( static_cast< double >( mPopulationSize ) ) );
            size_t selectionSize = selectionCount * selectionCount;

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

                // Save several weaker individuals if selectionSize < mPopulationSize;
                for ( size_t i = selectionCount, j = selectionSize; j < mPopulationSize; ++ i, ++ j )
                {
                    mPopulation[j] = mPopulation[i];
                }
            }

            // Crossover
            for ( int i = selectionCount - 1; i >= 0; -- i )
            {
                for ( int j = selectionCount - 1; j >= 0; -- j )
                {
                    if ( i != j )
                    {
                        PairPhenotypeFitness child;
                        child.first = Crossover( mPopulation[i].first, mPopulation[j].first );
                        mPopulation[ i * selectionCount + j ] = child;
                    }
                    else
                    {
                        mPopulation[ i * selectionCount + j ] = mPopulation[i];
                    }
                }
            }

            // Mutation
            for ( size_t i = 0; i < mPopulationSize; ++ i )
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
        size_t                  mPopulationSize;
        Population              mPopulation;
        PairPhenotypeFitness    mFittest;
    };

} // namespace GA

#endif // __GA_SOLVER_H__
