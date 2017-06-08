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

typedef enum {
    ROOM_OUT_OF_MEMORY, // You should exit program after this error
    ROOM_INVALID_COMMAND_LINE_PARAMETERS, // You should exit program after this error
    ROOM_CANNOT_OPEN_FILE, // You should exit program after this error
    ROOM_NULL_PARAMETER,
    ROOM_INVALID_PARAMETER,
    ROOM_EMAIL_ALREADY_EXISTS,
    ROOM_COMPANY_EMAIL_DOES_NOT_EXIST,
    ROOM_CLIENT_EMAIL_DOES_NOT_EXIST,
    ROOM_ID_ALREADY_EXIST,
    ROOM_ID_DOES_NOT_EXIST,
    ROOM_CLIENT_IN_ROOM,
    ROOM_ROOM_NOT_AVAILABLE,
    ROOM_RESERVATION_EXISTS,
    ROOM_NO_ROOMS_AVAILABLE,
    ROOM_SUCCESS,
} RoomReturn;

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
Room roomCreate(int id, int price, int num_ppl, char* working_hour, int difficulty,RoomReturn* Return);

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
