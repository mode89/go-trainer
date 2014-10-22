#include "cmn/platform.h"

CMN_WARNING_PUSH
CMN_WARNING_DISABLE_MSVC( 4625 4626 )
#include "gtest/gtest.h"
CMN_WARNING_POP

#include "ann/perceptron.h"
#include "ann/perceptron_genetic_algorithm_trainer.h"

#include <cmath>

using namespace ANN;

class FitnessOp
{
public:
    typedef std::vector< double > Sample;
    typedef std::vector< Sample > Samples;

    FitnessOp( const Samples & inputs, const Samples & outputs )
        : mInputs( inputs )
        , mOutputs( outputs )
    {}

    virtual double operator() ( ConstINetworkIn nw )
    {
        double totalError = 0.0;
        for ( size_t sampleIndex = 0, n = mInputs.size(); sampleIndex < n; ++ sampleIndex )
        {
            const Sample & outputs = nw->Compute( mInputs[ sampleIndex ] ); 

            double sampleError = 0.0;
            for ( Sample::size_type i = 0; i < outputs.size(); ++ i )
            {
                double error = outputs[i] - mOutputs[ sampleIndex ][ i ];
                sampleError += error * error;
            }

            totalError += sampleError;
        }

        return std::sqrt( totalError );
    }

    //ErrorFunctor & operator= ( const ErrorFunctor & );

private:
    const Samples &  mInputs;
    const Samples &  mOutputs;
};

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

    INetworkRef nw = std::make_shared< Perceptron >( layers );

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
    FitnessOp::Samples inputs( 4 );
    FitnessOp::Samples outputs( 4 );

    for ( uint32_t a = 0; a < 2; ++ a )
    {
        for ( uint32_t b = 0; b < 2; ++ b )
        {
            FitnessOp::Sample & input = inputs[ a * 2 + b ];
            FitnessOp::Sample & output = outputs[ a * 2 + b ];
            input.resize( 2 );
            output.resize( 1 );

            input[0] = static_cast< double >( a );
            input[1] = static_cast< double >( b );
            output[0] = ( a == b ) ? 0.4f : 0.6f;
        }
    }

    FitnessOp fitnessOp( inputs, outputs );
    IPerceptronGeneticAlgorithmTrainerRef trainer =
        CreatePerceptronGeneticAlgorithmTrainer(
            fitnessOp, inputs[0].size(), outputs[0].size(), 10 );
    while ( trainer->Step() > 0.01 );
}
