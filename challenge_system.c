#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>


#include "challenge_system.h"
#include "challenge.h"
#include "constants.h"
#include "visitor_room.h"

static Result challenge_best_time(ChallengeRoomSystem *sys,
                                  char **challenge_name, int *time);

static Result get_index_from_challenge_name (ChallengeRoomSystem *sys,
                                             char *challenge_name, int *index);

static Result get_index_from_challenge_id (ChallengeRoomSystem *sys,
                                           int challenge_id, int *index);

static Result get_index_from_room_name (ChallengeRoomSystem *sys,
                                        char *room_name, int *index);

static Result create_visitor_list (char *visitor_name, int id);

static Result get_visitor_name_from_id (ChallengeRoomSystem *sys,
                                        int visitor_id, char **visitor_name);

Result create_system(char *init_file, ChallengeRoomSystem **sys){
    if (init_file == NULL || sys == NULL){
        return NULL_PARAMETER;
    }
    FILE* kuku = fopen(init_file, "r");


}

Result destroy_system(ChallengeRoomSystem *sys, int destroy_time,
                      char **most_popular_challenge,
                      char **challenge_best_time){
    all_visitors_quit(sys, destroy_time);
    most_popular_challenge(sys, most_popular_challenge);
    challenge_best_time(challenge_best_time, sys);
}


Result visitor_arrive(ChallengeRoomSystem *sys, char *room_name,
                      char *visitor_name, int visitor_id,
                      Level level, int start_time){
    if (sys == NULL){
        return NULL_PARAMETER;
    }
    Visitors_list *new_visitor = NULL;
    Result result = create_visitor(
    if (result != OK){
        return result;
    }

    return visitor_enter_room(room_name, , level, start_time);
}


Result visitor_quit(ChallengeRoomSystem *sys, int visitor_id, int quit_time){
    if (quit_time < sys->last_activity){
        return ILLEGAL_TIME;
    }
    if  (sys == NULL) {
        return NULL_PARAMETER;
    }
    if (visitor_id == NULL){
        return ILLEGAL_PARAMETER;
    }
    char **visitor_name = NULL;
    if (get_visitor_name_from_id(sys, visitor_id, visitor_name)
        == MEMORY_PROBLEM){
        return MEMORY_PROBLEM;
    }
    visitor_quit_room(sys->visitors_list->visitor, quit_time);
}


Result all_visitors_quit(ChallengeRoomSystem *sys, int quit_time){
    if (quit_time < sys->last_activity){
        return ILLEGAL_TIME;
    }
    if  (sys == NULL) {
        return NULL_PARAMETER;
    }

}

Result system_room_of_visitor(ChallengeRoomSystem *sys,
                              char *visitor_name, char **room_name){
    if (sys == NULL){
        return NULL_PARAMETER;
    }
    if (visitor_name == NULL || room_name == NULL){ //what the problem if (room_name == NULL)?
        return ILLEGAL_PARAMETER;
    }
    Visitors_list *current = sys->visitors_list;
    while (current != NULL){
        if (strcmp(current->visitor->visitor_name, visitor_name) == 0) {
            room_name = malloc()////
        }
        current = current->next_visitor;
    }
    return NOT_IN_ROOM;
}



Result change_challenge_name(ChallengeRoomSystem *sys,
                             int challenge_id, char *new_name){
    if (sys == NULL || challenge_id == NULL || new_name == NULL){
        return NULL_PARAMETER;
    }
    int *index = NULL;
    if (get_index_from_challenge_id(sys ,challenge_id, index)
        == ILLEGAL_PARAMETER) {
        return ILLEGAL_PARAMETER;
    }
    return change_name(sys->system_challenges+*index, new_name);
}


Result change_system_room_name(ChallengeRoomSystem *sys,
                               char *current_name, char *new_name){
    if (sys == NULL || current_name == NULL || new_name == NULL){
        return NULL_PARAMETER;
    }
    int *index = NULL;
    if (get_index_from_room_name(sys, current_name, index)
        == ILLEGAL_PARAMETER) {
        return ILLEGAL_PARAMETER;
    }
    sys->system_rooms[*index].name = malloc(sizeof(new_name)+1);
    return change_room_name(sys->system_rooms+*index, new_name);
}


Result best_time_of_system_challenge(ChallengeRoomSystem *sys,
                                     char *challenge_name, int *time){
    if (sys == NULL || challenge_name == NULL){
        return NULL_PARAMETER;
    }
    int *index = NULL;
    if (get_index_from_challenge_name (sys, challenge_name, index)
        == ILLEGAL_PARAMETER){
        return ILLEGAL_PARAMETER;
    }
    return best_time_of_challenge(sys->system_challenges+*index, time);
}

Result most_popular_challenge(ChallengeRoomSystem *sys, char **challenge_name){
    if (sys == NULL || challenge_name == NULL){
        return NULL_PARAMETER;
    }
    int most_popular_visits = 0;
    int most_popular_index = 0;
    for (int i = 0; i < sys->num_of_challenges ; ++i) {
        int *visits = NULL;
        num_visits(sys->system_challenges+i, visits);
        if (most_popular_visits < *visits){
            most_popular_visits = *visits;
            most_popular_index = i;
        } else if (most_popular_visits == *visits
                   && 0 > strcmp(sys->system_challenges[i].name,
                                 sys->system_challenges
                                      [most_popular_index].name)){
            most_popular_visits = *visits;
            most_popular_index = i;
        }
    }
    *challenge_name =
            malloc(sizeof(sys->system_challenges[most_popular_index].name)+1);
    if (*challenge_name == NULL){
        return MEMORY_PROBLEM;
    }
    strcpy(*challenge_name,sys->system_challenges[most_popular_index].name);
    return OK;
}


static Result challenge_best_time(ChallengeRoomSystem *sys,
                                  char **challenge_name, int *time){
    int best_time = 0;
    int best_challenge_index = 0;
    for (int i = 0; i < sys->num_of_challenges ; ++i) {
        int *best_time_in_challenge = NULL;
        best_time_of_challenge(sys->system_challenges+i,
                               best_time_in_challenge);
        if (*best_time_in_challenge == NULL) {
            continue;
        }
        if (best_time > *best_time_in_challenge){
            best_time = *best_time_in_challenge;
            best_challenge_index = i;
        } else if (best_time == *best_time_in_challenge
                   && 0 > strcmp(sys->system_challenges[i].name,
                                 sys->system_challenges
                                 [best_challenge_index].name)){
            best_time = *best_time_in_challenge;
            best_challenge_index = i;
        }
    }
    *time= best_time;
    *challenge_name = sys->system_challenges[best_challenge_index].name;
    /////////////////////////////////////////////////
    return OK;
}

static Result get_index_from_challenge_name (ChallengeRoomSystem *sys,
                                             char *challenge_name, int *index){
    for (*index = 0 ; *index < sys->num_of_challenges; ++(*index)) {
        if (strcmp(sys->system_challenges[*index].name, challenge_name) == 0){
            break;
        }
    }
    if (*index == sys->num_of_challenges) {
        return ILLEGAL_PARAMETER;
    }
    return OK;
}

static Result get_index_from_challenge_id (ChallengeRoomSystem *sys,
                                           int challenge_id, int *index){
    for (*index = 0 ; *index < sys->num_of_challenges; ++(*index)) {
        if (sys->system_challenges[*index].id == challenge_id{
            break;
        }
    }
    if (*index == sys->num_of_challenges) {
        return ILLEGAL_PARAMETER;
    }
    return OK;
}

static Result get_index_from_room_name (ChallengeRoomSystem *sys,
                                        char *room_name, int *index){
    for (*index = 0; *index < sys->num_of_rooms; ++(*index)) {
        if (strcmp(sys->system_rooms[*index].name, room_name) == 0) {
            break;
        }
    }
    if (*index == sys->num_of_rooms){
        return ILLEGAL_PARAMETER;
    }
    return OK;
}

static Result create_visitor_list (char *visitor_name, int id) {

}

static Result add_visitor_to_list (Visitors_list *visitors_list,
                                   Visitors_list *new_visitor){

}

static Result get_visitor_name_from_id (ChallengeRoomSystem *sys,
                                        int visitor_id, char **visitor_name) {
    Visitors_list *current = sys->visitors_list;
    while (current != NULL) {
        if (current->visitor->visitor_id == visitor_id) {
            return make_str_copy(visitor_name, current->visitor->visitor_name);
        }
        current = current->next_visitor;
    }
}