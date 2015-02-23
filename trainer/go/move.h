#ifndef __GO_MOVE_H__
#define __GO_MOVE_H__

namespace go {

    enum MoveType
    {
        MOVE_TYPE_PLACE = 1,
        MOVE_TYPE_PASS,
    };

    struct Move
    {
        MoveType    type;
        unsigned    row;
        unsigned    column;

        Move()
            : type( MOVE_TYPE_PLACE )
            , row( -1 )
            , column( -1 )
        {}
    };

} // namespace go

#endif // __GO_MOVE_H__
