#ifndef __GO_STONE_H__
#define __GO_STONE_H__

#include "go/color.h"

namespace go {

    struct Stone
    {
        Color       color;
        unsigned    row;
        unsigned    column;
    };

} // namespace go

#endif // __GO_STONE_H__
