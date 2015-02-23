#ifndef __GO_PLAYER_H__
#define __GO_PLAYER_H__

#include "go/color.h"
#include "go/move.h"

namespace go {

    class Board;

    class IPlayer
    {
    public:
        virtual void
        Init( Color, unsigned boardSize ) = 0;

        virtual Move
        MakeMove( const Board & ) = 0;

        virtual
        ~IPlayer() {}
    };

} // namespace go

#endif // __GO_PLAYER_H__
