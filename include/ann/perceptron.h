#ifndef __ANN_PERCEPTRON_H__
#define __ANN_PERCEPTRON_H__

#include "ann/network.h"

#include <vector>

namespace ANN {

    class Perceptron : public INetwork
    {
    public:
        virtual const std::vector< double > &
        Compute( const std::vector< double > & ) const;

        virtual unsigned
        GetInputsCount() const { return mLayers[ 0 ].size(); }

        virtual unsigned
        GetOutputsCount() const { return mOutputs.size(); }

    public:
        struct Neuron
        {
            typedef std::vector< double > Weights;

            double  threshold;
            Weights weights;
        };

        typedef std::vector<Neuron> Neurons;
        typedef std::vector<Neurons> Layers;

        Perceptron( const Layers & );
        ~Perceptron();

        const Layers &
        GetLayers() { return mLayers; }

    private:
        typedef std::vector< std::vector< double > > Outputs;

        Layers              mLayers;
        mutable Outputs     mOutputs;
    };
    SHARED_PTR_TYPEDEFS( Perceptron );

} // namespace ANN

#endif // __ANN_PERCEPTRON_H__
