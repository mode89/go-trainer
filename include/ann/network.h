#ifndef __ANN_NETWORK_H__
#define __ANN_NETWORK_H__

#include "ann/types_fwd.h"
#include <vector>

namespace ANN {

    class INetwork
    {
    public:
        virtual const std::vector< double > &
        Compute( const std::vector< double > & ) const = 0;

        virtual unsigned
        GetInputsCount() const = 0;

        virtual unsigned
        GetOutputsCount() const = 0;

        virtual
        ~INetwork() {}
    };
    SHARED_PTR_TYPEDEFS( INetwork );

} // namespace ANN

#endif // __ANN_NETWORK_H__
