#ifndef __GNUGO_ENGINE_H__
#define __GNUGO_ENGINE_H__

#include "go/player.h"
#include "go/stone.h"
#include <list>
#include <string>
#include <ostream>

#if CMN_WIN32
    #include <windows.h>
#endif // CMN_WIN32

namespace gnugo {

    class Engine
    {
    public:
        std::string
        Execute( std::string command );

        void
        ClearBoard();

        bool
        IsLegal( go::Color, go::Move );

        void
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

        void
        Quit();

        void
        SetLogStream( std::ostream * s ) { mLogStream = s; }

    public:
        Engine( unsigned level, unsigned boardSize, unsigned seed = 0 );
        ~Engine();

    private:
        unsigned        mLevel;
        unsigned        mBoardSize;
        std::ostream *  mLogStream;

#if CMN_WIN32
        HANDLE      mStdoutRead;
        HANDLE      mStdoutWrite;
        HANDLE      mStdinRead;
        HANDLE      mStdinWrite;
#elif CMN_LINUX
        int         mChildPID;
        int         mPipes[2][2];
#endif // CMN_WIN32
    };

} // namespace gnugo

#endif // __GNUGO_ENGINE_H__
