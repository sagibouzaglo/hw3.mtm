/*
  room.h
  hw3

  Created by sagi bouzaglo on 27/05/2017.
  Copyright © 2017 sagi bouzaglo. All rights reserved.*/

#ifndef ROOM_H
#define ROOM_H

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "set.h"
#include "company.h"
//#include "order.h"

typedef struct room* Room;

typedef enum {
    ROOM_OUT_OF_MEMORY, // You should exit program after this error
    ROOM_SUCCESS,
    ROOM_INVALID_PARAMETER,

} RoomReturn;

/**
 * Allocates a new room,intialize it and return a pointer to the room
 *
 * @param id - room id.
 * @param price - price for ordering the room.
 * @param num_ppl - recommended number of people in room
 * @param working_hour - room working hours
 * @param difficulty - diffuculty of room.
 *
 * @return result
 * ROOM_INVALID_PARAMETER - one of the sent pointers is NULL.
 * ROOM_OUT_OF_MEMORY - allocation failed.
 * ROOM_SUCCESS - room created seccesfully.
 *
 * @return
 * pointer to the new room
 */
Room roomCreate(int id, int price, int num_ppl, char* working_hour,
                                            int difficulty,RoomReturn* Return);

/**
 * free all allocated memory for the room
 *
 * @param room -  pointer to the room.
 *
 */
void roomDestroy(void* room);

/**
 * Allocates a new room  and copy the sent room to the new room
 *
 * @param room - the room we want to copy.
 * @return result
 * ROOM_INVALID_PARAMETER - the new email.
 * ROOM_OUT_OF_MEMORY - allocation failed.
 * ROOM_SUCCESS - room created seccesfully.
 *
 * @return
 * pointer to the new copied room
 */
SetElement roomCopy(void* room);

/**
 * check if two room are identical
 *
 * @param room1 - pointer to the first checked room.
 * @param room2 - pointer to the second checked room.
 *
 * @return
 * true - the room are identical.
 * false - the rooms are different.
 */
int roomCompare(void* room1, void* room2);

/**
 * gets the id of the sent room
 *
 * @param room - a pointer to a room.
 *
 * @return
 * ERROR -pointer sent is NULL.
 * room->id - the room id.
 */
int getIdRoom(Room room);

/**
 * gets the price of the sent room
 *
 * @param room - a pointer to a room.
 *
 * @return
 * ERROR -pointer sent is NULL.
 * room->price - the room price.
 */
int getPriceRoom(Room room);

/**
 * gets the number of people recommended for the sent room
 *
 * @param room - a pointer to a room.
 *
 * @return
 * ERROR -pointer sent is NULL.
 * room->num_ppl - the room recommended number of people.
 */
int getNumPplRoom(Room room);

/**
 * gets the difficulty of the sent room
 *
 * @param room - a pointer to a room.
 *
 * @return
 * ERROR -pointer sent is NULL.
 * room->diffuclty - the room difficulty.
 */
int getDifficultyRoom(Room room);

/**
 * gets the opening hour of the sent room
 *
 * @param room - a pointer to a room.
 *
 * @return
 * ERROR -pointer sent is NULL.
 * room->open_hour - the room opening hour.
 */
int getOpenHRoom(Room room);

/**
 * gets the closing hour of the sent room
 *
 * @param room - a pointer to a room.
 *
 * @return
 * ERROR -pointer sent is NULL.
 * room->close_hour - the room closing hour.
 */
int getCloseHRoom(Room room);



#endif /* ROOM_H */
