#include "perceptron_genetic_algorithm_trainer.h"

namespace ANN {

    IPerceptronGeneticAlgorithmTrainerRef CreatePerceptronGeneticAlgorithmTrainer(
        const IPerceptronGeneticAlgorithmTrainer::FitnessOp & fitnessOp,
        unsigned inputsCount,
        unsigned outputsCount,
        unsigned populationSize )
    {
        return std::make_shared< PerceptronGeneticAlgorithmTrainer >(
            fitnessOp, inputsCount, outputsCount, populationSize );
    }

    PerceptronGeneticAlgorithmTrainer::PerceptronGeneticAlgorithmTrainer(
        const FitnessOp & fitnessOp,
        unsigned inputsCount,
        unsigned outputsCount,
        unsigned populationSize )
        : GA::Solver< PerceptronRef >( populationSize )
        , mFitnessOp( fitnessOp )
        , mInputsCount( inputsCount )
        , mOutputsCount( outputsCount )
        , mMutationProbability( 0.5f )
        , mMutationSpeed( 0.1f )
    {
    }

    PerceptronGeneticAlgorithmTrainer::~PerceptronGeneticAlgorithmTrainer()
    {
    }

    PerceptronRef PerceptronGeneticAlgorithmTrainer::CreateIndividual()
    {
        Perceptron::Layers layers( 4 );
        layers[0].resize( mInputsCount );
        layers[1].resize( mInputsCount * 2 );
        layers[2].resize( mInputsCount * 2 );
        layers[3].resize( mOutputsCount );

        std::uniform_real_distribution<> randDistr;

        for ( Perceptron::Layers::size_type layerIndex = 1; layerIndex < layers.size(); ++ layerIndex )
        {
            Perceptron::Neurons & layer = layers[layerIndex];

            for ( Perceptron::Neurons::size_type neuronIndex = 0; neuronIndex < layer.size(); ++ neuronIndex )
            {
                Perceptron::Neuron & neuron = layer[neuronIndex];

                neuron.threshold = randDistr( mRandomEngine );

                neuron.weights.resize( layers[layerIndex - 1].size() );
                for ( Perceptron::Neuron::Weights::size_type weightIndex = 0; weightIndex < neuron.weights.size(); ++ weightIndex)
                {
                    neuron.weights[weightIndex] = randDistr( mRandomEngine );
                }
            }
        }

        return std::make_shared< Perceptron >( layers );
    }

    double PerceptronGeneticAlgorithmTrainer::Fitness( const PerceptronRef & nw )
    {
        return mFitnessOp( nw );
    }

    PerceptronRef PerceptronGeneticAlgorithmTrainer::Crossover( const PerceptronRef & nw1, const PerceptronRef & nw2 )
    {
        Perceptron::Layers layers = nw1->GetLayers();
        const Perceptron::Layers & layers2 = nw2->GetLayers();

        std::uniform_real_distribution<> randDistr;

        for ( Perceptron::Layers::size_type layerIndex = 1; layerIndex < layers.size(); ++ layerIndex )
        {
            Perceptron::Neurons & layer = layers[layerIndex];
            const Perceptron::Neurons & layer2 = layers2[layerIndex];

            for ( Perceptron::Neurons::size_type neuronIndex = 0; neuronIndex < layer.size(); ++ neuronIndex )
            {
                Perceptron::Neuron & neuron = layer[neuronIndex];
                const Perceptron::Neuron & neuron2 = layer2[neuronIndex];

                if ( randDistr( mRandomEngine ) > 0.5 )
                {
                    neuron.threshold = neuron2.threshold;
                }

                for ( Perceptron::Neuron::Weights::size_type weightIndex = 0; weightIndex < neuron.weights.size(); ++ weightIndex )
                {
                    if ( randDistr( mRandomEngine ) > 0.5 )
                    {
                        neuron.weights[weightIndex] = neuron2.weights[weightIndex];
                    }
                }
            }
        }

        return std::make_shared< Perceptron >( layers );
    }

    PerceptronRef PerceptronGeneticAlgorithmTrainer::Mutation( const PerceptronRef & nw )
    {
        Perceptron::Layers layers = nw->GetLayers();

        std::uniform_real_distribution<> randDistr;

        for ( Perceptron::Layers::size_type layerIndex = 1; layerIndex < layers.size(); ++ layerIndex )
        {
            Perceptron::Neurons & layer = layers[layerIndex];
            for ( Perceptron::Neurons::size_type neuronIndex = 0; neuronIndex < layer.size(); ++ neuronIndex )
            {
                Perceptron::Neuron & neuron = layer[neuronIndex];

                if ( randDistr( mRandomEngine ) <= mMutationProbability )
                {
                    neuron.threshold += ( randDistr( mRandomEngine ) - 0.5f ) * mMutationSpeed;
                }

                for ( Perceptron::Neuron::Weights::size_type weightIndex = 0; weightIndex < neuron.weights.size(); ++ weightIndex )
                {
                    if ( randDistr( mRandomEngine ) <= mMutationProbability )
                    {
                        neuron.weights[weightIndex] += ( randDistr( mRandomEngine ) - 0.5f ) * mMutationSpeed;
                    }
                }
            }
        }

        return std::make_shared< Perceptron >( layers );
    }

    double PerceptronGeneticAlgorithmTrainer::Step()
    {
        return GA::Solver< PerceptronRef >::Step();
    }

} // namespace ANN
