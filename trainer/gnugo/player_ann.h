#ifndef __GNUGO_PLAYER_ANN_H__
#define __GNUGO_PLAYER_ANN_H__

#include "gnugo/player_base.h"
#include "opennn/vector.h"

#include <vector>

namespace OpenNN {
    class NeuralNetwork;
}

namespace gnugo {

    class PlayerAnn : public PlayerBase
    {
    public:
        void
        Init( go::Color, unsigned boardSize );

        go::Move
        MakeMove( const go::Board & );

    public:
        PlayerAnn( const OpenNN::NeuralNetwork &, Engine & );
        ~PlayerAnn();

    private:
        typedef OpenNN::Vector< double > Inputs;

        const OpenNN::NeuralNetwork &   mNetwork;
        Inputs                          mInputs;
    };

} // namespace gnugo

#endif // __GNUGO_PLAYER_ANN_H__
