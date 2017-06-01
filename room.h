//
//  room.h
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef room_h
#define room_h

#include <stdio.h>
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

void roomDestroy(Room room);

Room roomCopy(Room room);

int roomCompare(Room room1, Room room2);

int getIDroom(Room room);

int getPriceRoom(Room room);

int getNumPPlroom(Room room);

int getDifficultyRoom(Room room);

int getOpenHRoom(Room room);

int getCloseHRoom(Room room);

#endif /* room_h */