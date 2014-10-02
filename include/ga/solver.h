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
        virtual ~Solver() {}

        Phenotype Solve( uint32_t populationSize, double maxFitness )
        {
            // Generate initial population

            Population population;
            population.resize( populationSize );
            for ( uint32_t i = 0; i < populationSize; ++ i )
            {
                population[i].first = CreateIndividual();
                population[i].second = FLT_MAX;
            }

            // Iterating

            uint32_t selectionCount = static_cast< uint32_t >( sqrt( static_cast< double >( populationSize ) ) );
            uint32_t selectionSize = selectionCount * selectionCount;

            PairPhenotypeFitness fittest;
            do
            {
                // Selection
                {
                    // Calculate fitness
                    for ( uint32_t i = 0; i < populationSize; ++ i )
                    {
                        double fitness = Fitness( population[i].first );
                        population[i].second = fitness;
                    }

                    // Sort according to the fitness values
                    std::sort( population.begin(), population.end(), ComparePhenotypeByFitness );
                    fittest = population[0];
                    if ( fittest.second <= maxFitness ) break;

                    // Save several weaker individuals if selectionSize < populationSize;
                    for ( uint32_t i = selectionCount, j = selectionSize; j < populationSize; ++ i, ++ j )
                    {
                        population[j] = population[i];
                    }
                }

                // Crossover
                for ( uint32_t i = selectionCount - 1; i >= 0; -- i )
                {
                    for ( uint32_t j = selectionCount - 1; j >= 0; -- j )
                    {
                        if ( i != j )
                        {
                            PairPhenotypeFitness child;
                            child.first = Crossover( population[i].first, population[j].first );
                            population[ i * selectionCount + j ] = child;
                        }
                        else
                        {
                            population[ i * selectionCount + j ] = population[i];
                        }
                    }
                }

                // Mutation
                for ( uint32_t i = 0; i < populationSize; ++ i )
                {
                    PairPhenotypeFitness mutant;
                    mutant.first = Mutation( population[i].first );
                    population[i] = mutant;
                }

            } while ( fittest.second > maxFitness );

            return fittest.first;
        }

    private:
        static inline bool ComparePhenotypeByFitness( const PairPhenotypeFitness & p1, const PairPhenotypeFitness & p2 )
        {
            return p1.second < p2.second;
        }

    protected:
        virtual Phenotype
        CreateIndividual() = 0;

        virtual double
        Fitness( const Phenotype & ) = 0;

        virtual Phenotype
        Crossover( const Phenotype &, const Phenotype & ) = 0;

        virtual Phenotype
        Mutation( const Phenotype & ) = 0;
    };

} // namespace GA

#endif // __GA_SOLVER_H__
