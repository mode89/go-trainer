#ifndef __GNUGO_PLAYER_ANN_H__
#define __GNUGO_PLAYER_ANN_H__

#include "ann/types_fwd.h"
#include "gnugo/player_base.h"

#include <vector>

namespace gnugo {

    class PlayerAnn : public PlayerBase
    {
    public:
        void
        Init( go::Color, unsigned boardSize );

        go::Move
        MakeMove( const go::Board & );

    public:
        PlayerAnn( ANN::ConstINetworkIn, Engine & );
        ~PlayerAnn();

    private:
        typedef std::vector< double > Inputs;

        ANN::ConstINetworkRef   mNetwork;
        Inputs                  mInputs;
    };

} // namespace gnugo

#endif // __GNUGO_PLAYER_ANN_H__
