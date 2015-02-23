#ifndef __GNUGO_ENGINE_H__
#define __GNUGO_ENGINE_H__

#include "go/player.h"
#include "go/stone.h"
#include <list>
#include <string>
#include <windows.h>

namespace gnugo {

    class Engine
    {
    public:
        std::string
        Execute( std::string command );

        void
        ClearBoard();

        bool
        Play( go::Color, go::Move );

        go::Move
        Genmove( go::Color );

        void
        ListStones( std::list< go::Stone > &, go::Color );

        void
        ListStones( std::list< go::Stone > & );

        void
        UpdateBoard( go::Board & );

        void
        ShowBoard( go::Board & );

        unsigned
        GetBoardSize() const { return mBoardSize; }

        float
        GetScore( go::Color );

    public:
        Engine( unsigned level, unsigned boardSize, unsigned seed = 0 );
        ~Engine();

    private:
        unsigned    mLevel;
        unsigned    mBoardSize;

        HANDLE      mStdoutRead;
        HANDLE      mStdoutWrite;
        HANDLE      mStdinRead;
        HANDLE      mStdinWrite;
    };

} // namespace gnugo

#endif // __GNUGO_ENGINE_H__
