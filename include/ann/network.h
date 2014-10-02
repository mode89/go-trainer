#ifndef __ANN_NETWORK_H__
#define __ANN_NETWORK_H__

#include "cmn/shared_ptr_typedefs.h"

#include <memory>
#include <vector>

namespace ANN {

    class INetwork
    {
    public:
        virtual const std::vector< double > &
        Compute( const std::vector< double > & ) = 0;

        virtual
        ~INetwork() {}
    };
    SHARED_PTR_TYPEDEFS( INetwork );

} // namespace ANN

#endif // __ANN_NETWORK_H__
