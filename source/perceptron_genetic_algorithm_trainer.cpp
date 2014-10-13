#include "perceptron_genetic_algorithm_trainer.h"

namespace ANN {

    IPerceptronGeneticAlgorithmTrainerRef CreatePerceptronGeneticAlgorithmTrainer(
        const IPerceptronGeneticAlgorithmTrainer::FitnessOp & fitnessOp )
    {
        return std::make_shared< PerceptronGeneticAlgorithmTrainer >( fitnessOp );
    }

    PerceptronGeneticAlgorithmTrainer::PerceptronGeneticAlgorithmTrainer(
        const FitnessOp & fitnessOp,
        uint32_t inputsCount,
        uint32_t outputsCount )
        : mFitnessOp( fitnessOp )
        , mInputsCount( inputsCount )
        , mOutputsCount( outputsCount )
    {}

    PerceptronRef PerceptronGeneticAlgorithmTrainer::CreateIndividual()
    {
        Perceptron::Layers layers( 4 );
        layers[0].resize( mInputsCount );
        layers[1].resize( mInputsCount * 2 );
        layers[2].resize( mInputsCount * 2 );
        layers[3].resize( mOutputsCount );

        for ( Perceptron::Layers::size_type layerIndex = 1; layerIndex < layers.size(); ++ layerIndex )
        {
            Perceptron::Neurons & layer = layers[layerIndex];

            for ( Perceptron::Neurons::size_type neuronIndex = 0; neuronIndex < layer.size(); ++ neuronIndex )
            {
                Perceptron::Neuron & neuron = layer[neuronIndex];

                neuron.threshold = Random();

                neuron.weights.resize( layers[layerIndex - 1].size() );
                for ( Perceptron::Neuron::Weights::size_type weightIndex = 0; weightIndex < neuron.weights.size(); ++ weightIndex)
                {
                    neuron.weights[weightIndex] = Random( 2.0f ) - 1.0f;
                }
            }
        }

        return std::static_pointer_cast<Perceptron>( CreatePerceptron( layers ) );
    }

    double PerceptronGeneticAlgorithmTrainer::Fitness( const PerceptronRef & nw )
    {
        return mFitnessOperator( nw );
    }

    PerceptronRef PerceptronGeneticAlgorithmTrainer::Crossover( const PerceptronRef & nw1, const PerceptronRef & nw2 )
    {
        Perceptron::Layers layers = nw1->GetLayers();
        const Perceptron::Layers & layers2 = nw2->GetLayers();

        for ( Perceptron::Layers::size_type layerIndex = 1; layerIndex < layers.size(); ++ layerIndex )
        {
            Perceptron::Neurons & layer = layers[layerIndex];
            const Perceptron::Neurons & layer2 = layers2[layerIndex];

            for ( Perceptron::Neurons::size_type neuronIndex = 0; neuronIndex < layer.size(); ++ neuronIndex )
            {
                Perceptron::Neuron & neuron = layer[neuronIndex];
                const Perceptron::Neuron & neuron2 = layer2[neuronIndex];

                if ( Random() > 0.5f )
                {
                    neuron.threshold = neuron2.threshold;
                }

                for ( Perceptron::Neuron::Weights::size_type weightIndex = 0; weightIndex < neuron.weights.size(); ++ weightIndex )
                {
                    if ( Random() > 0.5f )
                    {
                        neuron.weights[weightIndex] = neuron2.weights[weightIndex];
                    }
                }
            }
        }

        return std::static_pointer_cast<Perceptron>( CreatePerceptron( layers ) );
    }

    PerceptronRef PerceptronGeneticAlgorithmTrainer::Mutation( const PerceptronRef & nw )
    {
        Perceptron::Layers layers = nw->GetLayers();

        for ( Perceptron::Layers::size_type layerIndex = 1; layerIndex < layers.size(); ++ layerIndex )
        {
            Perceptron::Neurons & layer = layers[layerIndex];
            for ( Perceptron::Neurons::size_type neuronIndex = 0; neuronIndex < layer.size(); ++ neuronIndex )
            {
                Perceptron::Neuron & neuron = layer[neuronIndex];

                if ( Random() <= mMutationProbability )
                {
                    neuron.threshold += ( Random() - 0.5f ) * mMutationSpeed;
                }

                for ( Perceptron::Neuron::Weights::size_type weightIndex = 0; weightIndex < neuron.weights.size(); ++ weightIndex )
                {
                    if ( Random() <= mMutationProbability )
                    {
                        neuron.weights[weightIndex] += ( Random() - 0.5f ) * mMutationSpeed;
                    }
                }
            }
        }

        return std::static_pointer_cast<Perceptron>( CreatePerceptron( layers ) );
    }

} // namespace ANN
