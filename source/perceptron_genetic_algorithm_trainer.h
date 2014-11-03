#ifndef __ANN_SOURCE_PERCEPTRON_GENETIC_ALGORITHM_TRAINER_H__
#define __ANN_SOURCE_PERCEPTRON_GENETIC_ALGORITHM_TRAINER_H__

#include "ann/perceptron_genetic_algorithm_trainer.h"
#include "ga/solver.h"

#include <random>

namespace ANN {

    class PerceptronGeneticAlgorithmTrainer :
        public IPerceptronGeneticAlgorithmTrainer,
        private GA::Solver< PerceptronRef >
    {
    public:
        double
        Step();

        void
        SetMutationProbability( double val ) { mMutationProbability = val; }

        void
        SetMutationSpeed( double val ) { mMutationSpeed = val; }

        PerceptronRef
        GetFittest() { return GA::Solver< PerceptronRef >::GetFittest(); }

    public:
        PerceptronGeneticAlgorithmTrainer(
            const FitnessOp &,
            unsigned inputsCount,
            unsigned outputsCount,
            unsigned populationSize );
        ~PerceptronGeneticAlgorithmTrainer();

    private:
        PerceptronRef
        CreateIndividual();

        double
        Fitness( const PerceptronRef & );

        PerceptronRef
        Crossover( const PerceptronRef &, const PerceptronRef & );

        PerceptronRef
        Mutation( const PerceptronRef & );

    private:
        typedef std::default_random_engine RandomEngine;

        FitnessOp           mFitnessOp;
        uint32_t            mSampleCount;

        uint32_t            mInputsCount;
        uint32_t            mOutputsCount;

        double              mMutationProbability;
        double              mMutationSpeed;

        RandomEngine        mRandomEngine;
    };

} // namesapce ANN

#endif // __ANN_SOURCE_PERCEPTRON_GENETIC_ALGORITHM_TRAINER_H__
