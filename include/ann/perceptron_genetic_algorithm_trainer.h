#ifndef __ANN_PERCEPTRON_GENETIC_ALGORITHM_TRAINER_H__
#define __ANN_PERCEPTRON_GENETIC_ALGORITHM_TRAINER_H__

#include "ann/perceptron.h"

#include <functional>

namespace ANN {

    class IPerceptronGeneticAlgorithmTrainer
    {
    public:
        typedef std::function< double( ConstPerceptronIn ) > FitnessOp;

        virtual double
        Step() = 0;

        virtual
        ~IPerceptronGeneticAlgorithmTrainer() {}
    };
    SHARED_PTR_TYPEDEFS( IPerceptronGeneticAlgorithmTrainer );

    IPerceptronGeneticAlgorithmTrainerRef
    CreatePerceptronGeneticAlgorithmTrainer(
        const IPerceptronGeneticAlgorithmTrainer::FitnessOp &,
        unsigned inputsCount,
        unsigned outputsCount,
        unsigned populationSize );

} // namespace ANN

#endif // __ANN_PERCEPTRON_GENETIC_ALGORITHM_TRAINER_H__
