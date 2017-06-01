//
//  room.c
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "room.h"
#include "company.h"
#include "order.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
#include <string.h>

#define HOURS_DAY 24
static bool hourWorking (char* working_hour, Room room);

struct room {
    int id;
    int price;
    int num_ppl;
    int open_hour; //working hour;
    int close_hour;
    int difficulty;
};


/** Allocates a new company */
Room roomCreate(int id, int price, int num_ppl, char* working_hour, int difficulty){
    Room room = malloc(sizeof(*room));
    if (!room) {
        return NULL;
    }

    room->id=id;
    room->price=price;
    room->num_ppl=num_ppl;
    if(!hourWorking(working_hour,room)){
        return NULL;
    }
    return room;
}

/** Frees an existing company object */
void roomDestroy(Room room){
    free(room);
}

/** Allocates a new company which is a copy of the argument */
void* roomCopy(Room room){
    if (!room) {
        return NULL;
    }
    return roomCreate(room->id,room->price,room->);
}
/** Returns true if both email company are identical */
int companyCompare(void* company1, void* company2) {
    assert(company1 && company2);
    return strcmp(((Company)company1)->email,((Company)company2)->email)==0;
}
char* getEmailCompany(Company company){
    if(!company){
        return NULL;
    }
    char* emailReturn = malloc(sizeof(strlen(company->email)+1));
    if(!emailReturn){
        return NULL;
    }
    strcpy(company->email,emailReturn);
    return emailReturn;
}

TechnionFaculty getFacultyOfCompuny(Company company){
    if(!company){
        return NULL;
    }
    return company->Faculty;
}
static bool hourWorking (char* working_hour, Room room){
    assert(room & working_hour);
    for(int i=0;i<strlen(working_hour);++i){
        if(*(working_hour + i) == '-'){
            *(working_hour+i)=NULL;
            room->open_hour=atol(working_hour);
            ++i;
            room->close_hour=atol(working_hour+i);
            break;
        }
    }
    if(room->open_hour>=room->close_hour || room->open_hour <0 || room->open_hour>HOURS_DAY ){
        room->close_hour=0;
        room->open_hour=0;
        return false;
    }
    return true;
}