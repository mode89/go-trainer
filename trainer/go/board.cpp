#include <algorithm>
#include "go/board.h"

namespace go {

    Board::Board( unsigned size )
        : mSize( size )
    {
        mCells.resize( mSize * mSize );
        Clear();
    }

    Board::~Board()
    {
    }

    void Board::Copy( const Board & board )
    {
        std::copy( board.mCells.begin(), board.mCells.end(), mCells.begin() );
    }

    void Board::Clear()
    {
        std::fill( mCells.begin(), mCells.end(), CELL_EMPTY );
    }

} // namspace go
