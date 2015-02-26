#include "cmn/platform.h"

CMN_WARNING_PUSH
CMN_WARNING_DISABLE_MSVC( 4625 4626 )
#include "gtest/gtest.h"
CMN_WARNING_POP

#include "ga/solver.h"

class Solver : public GA::Solver< double >
{
public:
    Solver( double result )
        : GA::Solver< double >( 10 )
        , mResult( result )
    {

    }

protected:
    double CreateIndividual()
    {
        return static_cast< double >( rand() ) / RAND_MAX;
    }

    double Fitness( const double & val )
    {
        return fabs( val - mResult );
    }

    double Crossover( const double & val1, const double & val2 )
    {
        return ( val1 + val2 ) / 2.0f;
    }

    double Mutation( const double & val )
    {
        return val + static_cast< double >( rand() ) * 0.02f / RAND_MAX - 0.01f;
    }

private:
    double mResult;
};
SHARED_PTR_TYPEDEFS( Solver );

TEST( GA, Solve )
{
    const double kResult = 0.7f;
    const double kEps = 0.01f;

    SolverRef solver = std::make_shared< Solver >( kResult );
    while ( solver->Step() > kEps );
    ASSERT_LE( fabs( solver->GetFittest() - kResult ), kEps );
}
