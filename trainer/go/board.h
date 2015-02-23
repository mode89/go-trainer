#ifndef __GO_BOARD_H__
#define __GO_BOARD_H__

#include "go/cell.h"
#include <vector>

namespace go {

    class Board
    {
    public:
        Cell &
        operator() ( unsigned row, unsigned column )
            { return mCells[ row * mSize + column ]; }

        const Cell &
        operator() ( unsigned row, unsigned column ) const
            { return mCells[ row * mSize + column ]; }

        unsigned
        GetSize() const { return mSize; }

        void
        Copy( const Board & );

        void
        Clear();

    public:
        Board( unsigned size );
        ~Board();

    private:
        unsigned            mSize;
        std::vector< Cell > mCells;
    };

} // namespace go

#endif // __GO_BOARD_H__
