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
        PerceptronGeneticAlgorithmTrainer(
            const FitnessOp &,
            unsigned inputsCount,
            unsigned outputsCount );
        ~PerceptronGeneticAlgorithmTrainer();

    private:
        PerceptronRef
        CreateIndividual();

    private:
        typedef std::default_random_engine RandomEngine;

        const FitnessOp &   mFitnessOp;
        uint32_t            mSampleCount;

        uint32_t            mInputsCount;
        uint32_t            mOutputsCount;

        double              mMutationProbability;
        double              mMutationSpeed;

        RandomEngine        mRandomEngine;
    };

} // namesapce ANN

#endif // __ANN_SOURCE_PERCEPTRON_GENETIC_ALGORITHM_TRAINER_H__
