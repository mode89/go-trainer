#ifndef __CMN_SHARED_PTR_TYPEDEFS_H__
#define __CMN_SHARED_PTR_TYPEDEFS_H__

#define SHARED_PTR_TYPEDEFS( T ) \
    typedef       std::shared_ptr <       T >            T ## Ref; \
	typedef       std::shared_ptr < const T >   Const ## T ## Ref; \
	typedef const std::shared_ptr <       T > &          T ## In; \
	typedef const std::shared_ptr < const T > & Const ## T ## In  \

#define SHARED_PTR_FORWARD_TYPEDEFS( T ) \
    class T; \
    SHARED_PTR_TYPEDEFS( T ) \

#endif // __CMN_SHARED_PTR_TYPEDEFS_H__
