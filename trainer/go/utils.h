#ifndef __GO_UTILS_H__
#define __GO_UTILS_H__

#include "go/cell.h"
#include "go/color.h"
#include "go/move.h"

namespace go {

    class Board;

    Move
    FindMove( const Board & prev, const Board & current );

    Color
    OppositeColor( Color );

    Cell
    CellFromColor( Color );

} // namespace go

#endif // __GO_UTILS_H__
