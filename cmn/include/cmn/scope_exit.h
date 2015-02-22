#ifndef __CMN_SCOPE_EXIT_H__
#define __CMN_SCOPE_EXIT_H__

namespace Cmn {

    template < typename F >
    class ScopeExit
    {
    public:
        ScopeExit( const F & f )
            : mF( f )
        {}

        ~ScopeExit()
        {
            mF();
        }

    private:
        const F mF;

        const ScopeExit &
        operator= ( const ScopeExit & );
    };

    template < typename F >
    ScopeExit< F > MakeScopeExit( const F & f )
    {
        return ScopeExit< F >( f );
    }

} // namespace Cmn

#endif // __CMN_SCOPE_EXIT_H__
