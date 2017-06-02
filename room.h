//
//  room.h
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef room_h
#define room_h

#include "company.h"
#include "order.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
#include <string.h>


typedef struct room* Room;


/**
 * roomCreate - Allocates a new room, and return the room type
 *
 *
 * @param id -
 * @param price-
 * @param num_ppl-
 * @param working_hour-
 * @param difficulty-
 */
Room roomCreate(int id, int price, int num_ppl, char* working_hour, int difficulty);

void roomDestroy(void* room);

void* roomCopy(void* room);

int roomCompare(void* room1, void* room2);

int getIdRoom(Room room);

int getPriceRoom(Room room);

int getNumPplRoom(Room room);

int getDifficultyRoom(Room room);

int getOpenHRoom(Room room);

int getCloseHRoom(Room room);



#endif /* room_h */