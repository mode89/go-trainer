#include "cmn/trace.h"
#include "go/board.h"
#include "go/utils.h"

namespace go {

    Move FindMove( const Board & prevBoard, const Board & currentBoard )
    {
        Move retval;

        CMN_ASSERT( prevBoard.GetSize() == currentBoard.GetSize() );
        unsigned size = prevBoard.GetSize();
        for ( unsigned row = 0; row < size; ++ row )
        {
            for ( unsigned column = 0; column < size; ++ column )
            {
                if ( prevBoard( row, column ) == CELL_EMPTY &&
                     currentBoard( row, column ) != CELL_EMPTY )
                {
                    retval.type = MOVE_TYPE_PLACE;
                    retval.row    = row;
                    retval.column = column;
                    return retval;
                }
            }
        }

        retval.type = MOVE_TYPE_PASS;
        return retval;
    }

    Color OppositeColor( Color color )
    {
        return ( color == COLOR_BLACK ) ? COLOR_WHITE : COLOR_BLACK;
    }

    Cell CellFromColor( Color color )
    {
        return ( color == COLOR_BLACK ) ? CELL_BLACK : CELL_WHITE;
    }

} // namespace go
