#ifndef CHALLENGE_SYSTEM_SYSTEM_FIELDS_H_
#define CHALLENGE_SYSTEM_SYSTEM_FIELDS_H_

#include "visitor_room.h"
#include "challenge_system.h"

char *name;
Challenge *system_challenges;
ChallengeRoom *system_rooms;
Visitors_list *visitors_list;
int last_activity;
int num_of_challenges;
int num_of_rooms;
#endif //CHALLENGE_SYSTEM_SYSTEM_FIELDS_H_
