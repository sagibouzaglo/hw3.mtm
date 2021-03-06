//
//  room.c
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "room.h"
#define HOURS_DAY 24
#define ERROR -1

/**
 * transfer the working hours from a string into int and save it in
 * room->open_hour and room->close_hour
 *
 * @param room - a pointer to a room.
 * @param working_hour - string holds the open and closing hours.
 *
 * @return
 * true - function succeed.
 * false - function failed.
 */
static bool hourWorking (char* working_hour, Room room);

struct room {
    int id;
    int price;
    int num_ppl;
    int open_hour; //working hour;
    int close_hour;
    int difficulty;
    char* working_h;
};

Room roomCreate(int id, int price, int num_ppl, char* working_hour,
                                            int difficulty,RoomReturn* Return){
    if(!working_hour){
        *Return=ROOM_INVALID_PARAMETER;
        return NULL;
    }
    Room room = malloc(sizeof(*room));
    if (!room) {
        *Return=ROOM_OUT_OF_MEMORY;
        return NULL;
    }
    room->id=id;
    room->price=price;
    room->num_ppl=num_ppl;
    room->difficulty=difficulty;
    room->working_h = malloc(sizeof(char)*(strlen(working_hour)+1));
    if(!room->working_h){
        return NULL;
    }
    strcpy(room->working_h ,working_hour);

    if(!hourWorking(working_hour,room)){
        *Return=ROOM_INVALID_PARAMETER;
        return NULL;
    }
    *Return=ROOM_SUCCESS;
    return room;
}

char* getWorkigHRoom(Room room){
    assert(room);
    assert(room->working_h);
    char* workH = malloc(sizeof(char)*(strlen(room->working_h)+1));
    if(!workH) return NULL;
    strcpy(workH,room->working_h);
    return workH;
}

void roomDestroy(void* room){
    if(!room) return;
    free(((Room)room)->working_h);
    free(room);
}

SetElement roomCopy(void* room){
    assert(room);
    RoomReturn Return=ROOM_SUCCESS;
    return roomCreate(((Room)room)->id,((Room)room)->price,
                            ((Room)room)->num_ppl,((Room)room)->working_h,
                                            ((Room)room)->difficulty,&Return);
}

int roomCompare(void* room1, void* room2) {
    assert(room1 && room2);
    return (((Room)room1)->id==((Room)room2)->id)? 0 : 1;
}

int getIdRoom(Room room){
    assert(room);
    return room->id;
}

int getPriceRoom(Room room){
    assert(room);
    return room->price;
}

int getNumPplRoom(Room room){
    assert(room);
    return room->num_ppl;
}

int getDifficultyRoom(Room room){
    assert(room);
    return room->difficulty;
}

int getOpenHRoom(Room room){
    assert(room);
    return room->open_hour;
}

int getCloseHRoom(Room room){
    assert(room);
    return room->close_hour;
}

static bool hourWorking (char* working_hour, Room room){
    assert(room && working_hour);
    for(int i=0;i<strlen(working_hour);++i){
        if(*(working_hour + i) == '-'){
            working_hour[i]='\0';
            room->open_hour=(int)atol(working_hour);
            ++i;
            room->close_hour=(int)atol(working_hour+i);
            break;
        }
    }
    if(room->open_hour>=room->close_hour ||
                            room->open_hour <0 ||
                                    room->open_hour>HOURS_DAY ){
        room->close_hour=0;
        room->open_hour=0;
        return false;
    }
    return true;
}
