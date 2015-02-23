#include "ann/network.h"
#include "cmn/trace.h"
#include "gnugo/engine.h"
#include "gnugo/player_ann.h"
#include "go/board.h"
#include "go/utils.h"

#include <algorithm>

namespace gnugo {

    using namespace ANN;
    using namespace go;

    PlayerAnn::PlayerAnn( ConstINetworkIn network, Engine & engine )
        : PlayerBase( engine )
        , mNetwork( network )
    {
    }

    PlayerAnn::~PlayerAnn()
    {
    }

    void PlayerAnn::Init( Color color, unsigned boardSize )
    {
        PlayerBase::Init( color, boardSize );

        unsigned cellCount = boardSize * boardSize;
        CMN_ASSERT( mNetwork->GetInputsCount() == cellCount );
        CMN_ASSERT( mNetwork->GetOutputsCount() == ( cellCount + 1 ) );

        mInputs.resize( cellCount );
    }

    Move PlayerAnn::MakeMove( const Board & board )
    {
        unsigned boardSize = board.GetSize();
        unsigned cellCount = boardSize * boardSize;

        // Prepare network inputs

            for ( unsigned row = 0; row < boardSize; ++ row )
            {
                unsigned offset = row * boardSize;
                for ( unsigned column = 0; column < boardSize; ++ column )
                {
                    double & input = mInputs[ column + offset ];
                    Cell cell = board( row, column );
                    if ( cell == CELL_EMPTY )
                    {
                        input = 0.0;
                    }
                    else if ( cell == CellFromColor( mColor ) )
                    {
                        input = 1.0;
                    }
                    else
                    {
                        input = -1.0;
                    }
                }
            }

        // Run the network

            const std::vector< double > networkOutputs = mNetwork->Compute( mInputs );

        // Parse network outputs

            typedef std::pair< double, unsigned > ValueIndexPair;
            std::vector< ValueIndexPair > valueIndices;
            valueIndices.reserve( networkOutputs.size() );
            for ( size_t index = 0, n = networkOutputs.size(); index < n; ++ index )
            {
                valueIndices.push_back( std::make_pair( networkOutputs[ index ], index ) );
            }
            std::sort( valueIndices.begin(), valueIndices.end(),
                [] ( const ValueIndexPair & lh, const ValueIndexPair & rh ) {
                    return lh.first < rh.first; } );

            for ( auto & vi : valueIndices )
            {
                Move move;
                if ( vi.second == cellCount )
                {
                    move.type = MOVE_TYPE_PASS;
                }
                else
                {
                    move.type   = MOVE_TYPE_PLACE;
                    move.row    = vi.second / boardSize;
                    move.column = vi.second % boardSize;
                }

                if ( mEngine.Play( mColor, move ) )
                {
                    return move;
                }
            }

        Move move;
        move.type = MOVE_TYPE_PASS;
        return move;
    }

} // namespace gnugo
