#include "ann/perceptron.h"
#include "cmn/trace.h"
#include "ga/solver.h"

#include <cmath>

namespace ANN {

    static inline double Random( double max = 1.0f )
    {
        return rand() * max / RAND_MAX;
    }

    class GASolver : public GA::Solver<PerceptronRef>
    {
    public:
        GASolver(
            IErrorFunctorIn errorFunctor,
            uint32_t sampleCount,
            uint32_t inputsCount,
            uint32_t outputsCount,
            double multationProbability,
            double mutationSpeed )
            : mErrorFunctor( errorFunctor )
            , mSampleCount( sampleCount )
            , mInputsCount( inputsCount )
            , mOutputsCount( outputsCount )
            , mMutationProbability( multationProbability )
            , mMutationSpeed( mutationSpeed )
        {}

        PerceptronRef CreateIndividual()
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

        double Fitness( const PerceptronRef & nw )
        {
            double rmsError = 0.0f;

            for ( uint32_t i = 0; i < mSampleCount; ++ i )
            {
                double error = (*mErrorFunctor)( nw, i );
                rmsError += error * error;
            }

            return sqrt( rmsError / mSampleCount );
        }

        PerceptronRef Crossover( const PerceptronRef & nw1, const PerceptronRef & nw2 )
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

        PerceptronRef Mutation( const PerceptronRef & nw )
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

    private:
        IErrorFunctorRef    mErrorFunctor;
        uint32_t            mSampleCount;

        uint32_t            mInputsCount;
        uint32_t            mOutputsCount;

        double              mMutationProbability;
        double              mMutationSpeed;
    };

    INetworkRef TrainPerceptron(
        IErrorFunctorIn errorFunctor,
        double rmsError,
        uint32_t sampleCount,
        uint32_t inputsCount,
        uint32_t outputsCount )
    {
        uint32_t populationSize = 2 * inputsCount * inputsCount + 2 * inputsCount
            + 4 * inputsCount * inputsCount + 2 * inputsCount
            + 2 * inputsCount * outputsCount + outputsCount;
        GASolver solver( errorFunctor, sampleCount, inputsCount, outputsCount, 1.0f / populationSize, 0.1f );
        return solver.Solve( populationSize, rmsError );
    }

    static inline double ActivationFunction( double x )
    {
        return 1.0f / ( 1.0f + std::exp( -x ) );
    }

    INetworkRef CreatePerceptron( const Perceptron::Layers & layers )
    {
        return std::make_shared<Perceptron>( layers );
    }

    Perceptron::Perceptron( const Layers & layers )
        : mLayers( layers )
    {
        mOutputs.resize( layers.size() );
        for ( Outputs::size_type i = 0; i < layers.size(); ++ i )
        {
            mOutputs[i].resize( layers[i].size() );
        }
    }

    Perceptron::~Perceptron()
    {

    }

    const std::vector< double > & Perceptron::Compute( const std::vector< double > & inputs )
    {
        // Save inputs
        for ( Neurons::size_type neuron = 0; neuron < mLayers[0].size(); ++ neuron )
        {
            mOutputs[0][neuron] = inputs[neuron];
        }

        // Compute each layer above the input layer
        for ( Layers::size_type layerIndex = 1; layerIndex < mLayers.size(); ++ layerIndex )
        {
            const Neurons & layer = mLayers[layerIndex];
            const Outputs::value_type & prevOutputs = mOutputs[layerIndex - 1];

            // Compute each neuron in the layer
            for ( Neurons::size_type neuronIndex = 0; neuronIndex < layer.size(); ++ neuronIndex )
            {
                const Neuron & neuron = layer[neuronIndex];

                // Accumulate weighted inputs of the neuron
                double sum = 0.0f;
                for ( Neuron::Weights::size_type link = 0; link < neuron.weights.size(); ++ link )
                {
                    sum += prevOutputs[link] * neuron.weights[link];
                }

                // Save output of the neuron
                mOutputs[layerIndex][neuronIndex] = ActivationFunction( sum - neuron.threshold );
            }
        }

        return mOutputs.back();
    }

} // namespace ANN
