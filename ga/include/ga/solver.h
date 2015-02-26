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
        double
        Step();

        Phenotype
        GetFittest() const { return mFittest.first; }

    public:
        Solver( size_t populationSize );
        virtual ~Solver();

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
