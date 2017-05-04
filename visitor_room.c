#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "visitor_room.h"

static Result find_request_challenge_index(ChallengeRoom *room,
                                           Level level, int *index);

static Result make_str_copy(char **str1, char *str2);

Result init_challenge_activity(ChallengeActivity *activity,
                               Challenge *challenge){
    if (activity == NULL || challenge == NULL){
        return NULL_PARAMETER;
    }
    activity->challenge = challenge;
    activity->visitor = NULL;
    activity->start_time = 0;
    return OK;
}

Result reset_challenge_activity(ChallengeActivity *activity) {
    if (activity == NULL){
        return NULL_PARAMETER;
    }
    activity->challenge=NULL;
    activity->visitor = NULL;
    activity->start_time = 0;
    return OK;
}

Result init_visitor(Visitor *visitor, char *name, int id){
    if (visitor == NULL || name == NULL){
        return NULL_PARAMETER;
    }
    visitor->current_challenge = NULL;
    visitor->visitor_id = id;
    visitor->room_name = NULL;
    return make_str_copy(&(visitor->visitor_name), name);
}

Result reset_visitor(Visitor *visitor){
    if (visitor == NULL){
        return NULL_PARAMETER;
    }
    free(visitor->visitor_name);
    visitor->visitor_name = NULL;
    visitor->visitor_name = NULL;
    visitor->visitor_id = 0;
    visitor->current_challenge = NULL;
    visitor->room_name = NULL;
    return OK;
}

Result init_room(ChallengeRoom *room, char *name, int num_challenges){
    if (room == NULL || name == NULL){
        return NULL_PARAMETER;
    }
    if (num_challenges < 1) {
        return ILLEGAL_PARAMETER;
    }
    if (make_str_copy(&(room->name), name) == MEMORY_PROBLEM) {
        return MEMORY_PROBLEM;
    }
    room->challenges = malloc(sizeof(room->challenges)*num_challenges);
    if (room->challenges == NULL) {
        free(room->name);
        room->name = NULL;
        return MEMORY_PROBLEM;
    }
    reset_challenge_activity(room->challenges);
    room->num_of_challenges=num_challenges;
    return OK;
}

Result reset_room(ChallengeRoom *room){
    free(room->name);
    room->name = NULL;
    room->num_of_challenges = 0;
    reset_challenge_activity(room->challenges);
    free(room->challenges);
    room->challenges = NULL;
    return OK;
}

Result num_of_free_places_for_level(ChallengeRoom *room,
                                    Level level, int *places){
    if (room == NULL){
        return NULL_PARAMETER;
    }
    int count = 0;
    int all_levels_count = 0;
    for (int i = 0 ; i < room->num_of_challenges ; i++){
        if (room->challenges[i].visitor == NULL){
            all_levels_count++;
            if (room->challenges[i].challenge->level == level){
                count++;
            }
        }
    }
    *places = count;
    if (level == All_Levels){
        *places = all_levels_count;
    }
    return OK;
}

Result change_room_name(ChallengeRoom *room, char *new_name){
    if (room == NULL || new_name == NULL){
        return NULL_PARAMETER;
    }
    free (room->name);
    room->name = NULL;
    return make_str_copy(&(room->name), new_name);
}

Result room_of_visitor(Visitor *visitor, char **room_name){
    if (visitor == NULL || room_name == NULL) {
        return NULL_PARAMETER;
    }
    return make_str_copy(room_name, *visitor->room_name);
}

Result visitor_enter_room(ChallengeRoom *room, Visitor *visitor,
                          Level level, int start_time){
    if (room == NULL || visitor == NULL) {
        return NULL_PARAMETER;
    }
    char *room_visitor = NULL;
    room_of_visitor(visitor, &room_visitor);
    if (strcmp(room_visitor, room->name) == 0) {
        return ALREADY_IN_ROOM;
    }
    int *places = NULL;
    num_of_free_places_for_level(room, level, places);
    if (*places == 0){
        return NO_AVAILABLE_CHALLENGES;
    }
    int *index = NULL;
    find_request_challenge_index(room, level, index);
    visitor->current_challenge->challenge = room->challenges[*index].challenge;
    visitor->current_challenge->start_time = start_time;
    return OK;
}

Result visitor_quit_room(Visitor *visitor, int quit_time){
    if (visitor == NULL){
        return NULL_PARAMETER;
    }
    if (visitor->room_name == NULL) {
        return NOT_IN_ROOM;
    }
    int total_time = quit_time - visitor->current_challenge->start_time;
    int best_time = NULL;
    best_time_of_challenge(visitor->current_challenge->challenge , &best_time);
    if (total_time < best_time){
        return set_best_time_of_challenge(visitor->current_challenge->challenge,
                                          total_time);
    }
    return OK;
}

static Result find_request_challenge_index(ChallengeRoom *room,
                                    Level level, int *index){
    *index = -1;
    for (int i = 0; i < room->num_of_challenges; ++i) {
        if (room->challenges[i].visitor == NULL) {
            if (level == All_Levels
                || room->challenges[i].challenge->level == level) {
                if (*index == -1
                    || strcmp(room->challenges[i].challenge->name,
                              room->challenges[*index].challenge->name) > 0) {
                    *index = i;
                }
            }
        }
    }
    return OK;
}

static Result make_str_copy(char **str1, char *str2){
    *str1 = malloc(sizeof(str2)+1);
    if (*str1 == NULL){
        return MEMORY_PROBLEM;
    }
    strcpy(*str1, str2);
    return OK;
}