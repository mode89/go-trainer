#include "cmn/platform.h"

CMN_WARNING_PUSH
CMN_WARNING_DISABLE_MSVC( 4625 4626 )
#include "gtest/gtest.h"
CMN_WARNING_POP

#include "ann/perceptron.h"

#include <cmath>

using namespace ANN;

class ErrorFunctor : public IErrorFunctor
{
public:
    typedef std::vector< double > Sample;
    typedef std::vector<Sample> Samples;

    ErrorFunctor( const Samples & inputs, const Samples & outputs )
        : mInputs( inputs )
        , mOutputs( outputs )
    {}

    virtual double operator() ( const INetworkRef & nw, uint32_t sampleIndex )
    {
        const Sample & outputs = nw->Compute( mInputs[sampleIndex] );

        double rmsError = 0.0f;
        for ( Sample::size_type i = 0; i < outputs.size(); ++ i )
        {
            double error = outputs[i] - mOutputs[sampleIndex][i];
            rmsError += error * error;
        }

        return std::sqrt( rmsError );
    }

    ErrorFunctor & operator= ( const ErrorFunctor & );

private:
    const Samples &  mInputs;
    const Samples &  mOutputs;
};
SHARED_PTR_TYPEDEFS( ErrorFunctor );

TEST( ANN, PerceptronXor )
{
    Perceptron::Layers layers( 3 );

    layers[0].resize( 2 );
    layers[1].resize( 2 );
    layers[2].resize( 1 );

    layers[1][0].threshold = 0.5f;
    layers[1][0].weights.resize( 2 );
    layers[1][0].weights[0] = 1.0f;
    layers[1][0].weights[1] = 1.0f;

    layers[1][1].threshold = 1.5f;
    layers[1][1].weights.resize( 2 );
    layers[1][1].weights[0] = 1.0f;
    layers[1][1].weights[1] = 1.0f;

    layers[2][0].threshold = 0.2f;
    layers[2][0].weights.resize( 2 );
    layers[2][0].weights[0] = 1.0f;
    layers[2][0].weights[1] = -1.0f;

    INetworkRef nw = CreatePerceptron( layers );

    for ( int a = 0; a < 2; ++ a )
    {
        for ( int b = 0; b < 2; ++ b )
        {
            std::vector< double > inputs( 2 );
            inputs[0] = static_cast< double >( a );
            inputs[1] = static_cast< double >( b );

            const std::vector< double > & outputs = nw->Compute( inputs );

            if ( a == b )
            {
                ASSERT_LT( outputs[0], 0.5f );
            }
            else
            {
                ASSERT_GT( outputs[0], 0.5f );
            }
        }
    }
}

TEST( ANN, PerceptronXorTraining )
{
    ErrorFunctor::Samples inputs( 4 );
    ErrorFunctor::Samples outputs( 4 );

    for ( uint32_t a = 0; a < 2; ++ a )
    {
        for ( uint32_t b = 0; b < 2; ++ b )
        {
            ErrorFunctor::Sample & input = inputs[ a * 2 + b ];
            ErrorFunctor::Sample & output = outputs[ a * 2 + b ];
            input.resize( 2 );
            output.resize( 1 );

            input[0] = static_cast< double >( a );
            input[1] = static_cast< double >( b );
            output[0] = ( a == b ) ? 0.4f : 0.6f;
        }
    }

    ErrorFunctorRef func = std::make_shared<ErrorFunctor>( inputs, outputs );
    INetworkRef nw = TrainPerceptron( func, 0.01f, 4, 2, 1 );
}
