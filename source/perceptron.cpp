#include "ann/perceptron.h"

#include <cmath>

namespace ANN {

    static inline double ActivationFunction( double x )
    {
        return 1.0f / ( 1.0f + std::exp( -x ) );
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

    const std::vector< double > & Perceptron::Compute( const std::vector< double > & inputs ) const
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
