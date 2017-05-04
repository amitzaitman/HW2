#ifndef SYSTEM_ADDITIONAL_TYPES_h_
#define SYSTEM_ADDITIONAL_TYPES_h_

#include "visitor_room.h"
#include "challenge_system.h"

typedef struct SVisitors_list_cell {
    Visitor *visitor;
    struct SVisitors_list_cell *next_visitor;
} Visitors_list_cell;

#endif //SYSTEM_ADDITIONAL_TYPES_h_