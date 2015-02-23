#include "cmn/trace.h"
#include "gnugo/engine.h"
#include "gnugo/player_base.h"
#include "go/board.h"
#include "go/utils.h"

namespace gnugo {

    using namespace go;

    PlayerBase::PlayerBase( Engine & engine )
        : mEngine( engine )
        , mColor( COLOR_UNKNOWN )
    {
    }

    PlayerBase::~PlayerBase()
    {
    }

    void PlayerBase::Init( Color color, unsigned boardSize )
    {
        mColor = color;
    }

} // namespace gnugo
