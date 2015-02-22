#if defined( EXCEPTION_NAMESPACE ) && defined( EXCEPTION_CODES )

    CMN_WARNING_PUSH
    CMN_WARNING_DISABLE_MSVC( 4996 ) // Deprecated function

    #define C( code, message ) \
        class code : public std::exception \
        { \
        public: \
            template < typename ... Args > \
            code( Args ... args ) { \
                char buffer[ 4096 ]; \
                std::sprintf( buffer, CMN_STRINGIFY2( EXCEPTION_NAMESPACE ) "::" #code " : " message, args... ); \
                mWhat = buffer; \
            } \
            const char * what() const throw() { \
                return mWhat.c_str(); \
            } \
        private: \
            std::string mWhat; \
        }; \

    namespace EXCEPTION_NAMESPACE {
        EXCEPTION_CODES
    };

    #undef C

    CMN_WARNING_POP

#else // defined( EXCEPTION_NAMESPACE ) && defined( EXCEPTION_CODES )

    #if !defined( EXCEPTION_NAMESPACE )
        #error EXCEPTION_NAMESPACE is undefined
    #endif

    #if !defined( EXCEPTION_CODES )
        #error EXCEPTION_CODES is undefined
    #endif

#endif // defined( EXCEPTION_NAMESPACE ) && defined( EXCEPTION_CODES )
