//
//  room_test.c
//  hw3
//
//  Created by sagi bouzaglo on 18/06/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

//#include "list_mtm/test_utilities.h"
//#include "../room.h"
#include <string.h>
#include "test_utilities.h"
#include "room.h"

static bool testRoomCreate() {
    RoomReturn Result=ROOM_SUCCESS;
    ASSERT_TEST(roomCreate(0, 0, 0, NULL, 0, &Result) == NULL);
    ASSERT_TEST(Result==ROOM_INVALID_PARAMETER);
    char* hours = "00-10";
    ASSERT_TEST(roomCreate(0, 0, 0, hours, 0, &Result) != NULL);
    ASSERT_TEST(Result==ROOM_SUCCESS);
    return true;
}

static bool testGetWorkigHRoom(){
    RoomReturn Result=ROOM_SUCCESS;
    char* hours = "00-10";
    Room room = roomCreate(0, 0, 0, hours, 0, &Result);
    ASSERT_TEST(strcmp(getWorkigHRoom(room),hours)==0);
    roomDestroy(room);
    return true;
}

static bool testRoomCompare() {
    RoomReturn Result=ROOM_SUCCESS;
    char* hour = "00-20";
    Room room = roomCreate(0, 0, 0, hour, 0, &Result);
    char* hours = "00-10";
    Room room2 = roomCreate(0, 0, 0, hours, 0, &Result);
    ASSERT_TEST(roomCompare(room,room2)==0);
    Room room3 = roomCreate(10, 0, 0, hour, 0, &Result);
    ASSERT_TEST(roomCompare(room,room3) !=0);
    roomDestroy(room);
    roomDestroy(room2);
    roomDestroy(room3);
    return true;
}

static bool testGetIdRoom(){
    RoomReturn Result=ROOM_SUCCESS;
    char* hour = "00-20";
    Room room = roomCreate(0, 0, 0, hour, 0, &Result);
    ASSERT_TEST(getIdRoom(room)==0);
    roomDestroy(room);
    return true;
}

static bool testGetPriceRoom(){
    RoomReturn Result=ROOM_SUCCESS;
    char* hour = "00-20";
    Room room = roomCreate(0, 0, 0, hour, 0, &Result);
    ASSERT_TEST(getPriceRoom(room)==0);
    roomDestroy(room);
    return true;
}

static bool testGetNumPplRoom(){
    RoomReturn Result=ROOM_SUCCESS;
    char* hour = "00-20";
    Room room = roomCreate(0, 0, 0, hour, 0, &Result);
    ASSERT_TEST(getNumPplRoom(room)==0);
    roomDestroy(room);
    return true;
}

static bool testGetDifficultyRoom(){
    RoomReturn Result=ROOM_SUCCESS;
    char* hour = "00-20";
    Room room = roomCreate(0, 0, 0, hour, 0, &Result);
    ASSERT_TEST(getDifficultyRoom(room)==0);
    roomDestroy(room);
    return true;
}

static bool testGetOpenHRoom(){
    RoomReturn Result=ROOM_SUCCESS;
    char* hour = "00-20";
    Room room = roomCreate(0, 0, 0, hour, 0, &Result);
    ASSERT_TEST(getOpenHRoom(room)==0);
    roomDestroy(room);
    return true;
}

static bool testGetCloseHRoom(){
    RoomReturn Result=ROOM_SUCCESS;
    char* hour = "00-20";
    Room room = roomCreate(0, 0, 0, hour, 0, &Result);
    ASSERT_TEST(getCloseHRoom(room)==20);
    roomDestroy(room);
    return true;
}

static bool testRoomDestroy(){
    RoomReturn Result=ROOM_SUCCESS;
    Room room = roomCreate(0, 0, 0, NULL, 0, &Result);    escaperDestroy(escaper);
    roomDestroy(room);
    return true;
}

int main (int argv, char** arc){
    RUN_TEST(testRoomCreate);
    RUN_TEST(testGetWorkigHRoom);
    RUN_TEST(testRoomCompare);
    RUN_TEST(testGetIdRoom);
    RUN_TEST(testGetPriceRoom);
    RUN_TEST(testGetNumPplRoom);
    RUN_TEST(testGetDifficultyRoom);
    RUN_TEST(testGetOpenHRoom);
    RUN_TEST(testGetCloseHRoom);
    RUN_TEST(testRoomDestroy);
    return 0;
}

