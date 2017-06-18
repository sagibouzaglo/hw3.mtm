//
//  order_test.c
//  hw3
//
//  Created by sagi bouzaglo on 18/06/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "test_utilities.h"
#include "order.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


/*
 Order orderCreate(char* time, Escaper escaper, int num_ppl, Company company1,
 int room_id,OrderReturn* Result){
 
 if (!escaper || !company1) {
 *Result= ORD_NULL_PARAMETER;
 return NULL;
 }
 Set roomsComp = getCompanyRooms(company1);
 if(!roomsComp) return NULL;
 *Result = ORD_NO_ROOMS_AVAILABLE;
 SET_FOREACH(Room,i_room,roomsComp){
 if(room_id ==getIdRoom(i_room)){
 *Result = ORD_SUCCESS;
 }
 }
 if(*Result != ORD_SUCCESS){
 return NULL;
 }
 Order order = malloc(sizeof(*order));
 if (!order) {
 *Result= ORD_OUT_OF_MEMORY;
 return NULL;
 }
 order->time=malloc(sizeof(char)*(strlen(time)+1));
 if(!order->time) {
 *Result = ORD_OUT_OF_MEMORY;
 return NULL;
 }
 order->company=company1;
 strcpy(order->time,time);
 if(!hourOrder (time,order)){
 return NULL;
 }
 order->escaper=escaper;
 order->num_ppl = num_ppl;
 order->room_id=room_id;
 order->tot_price=CalculatePrice(findAndgetPriceRoom(company1,room_id),
 num_ppl, order);
 return order;
 }
 
 void orderDestroy(void* order){
 if(!order) return;
 free(((Order)order)->time);
 free(order);
 }
 
 ListElement orderCopy(void* order){
 assert(order);
 OrderReturn Result=ORD_SUCCESS;
 return orderCreate(((Order)order)->time, ((Order)order)->escaper ,
 ((Order)order)->num_ppl,((Order)order)->company,
 ((Order)order)->room_id ,&Result);
 }
 
 int compareOrders(void* order1,void* order2){
 if (((Order)order1)->hour > ((Order)order2)->hour){
 return 1;
 } else if (((Order)order1)->hour < ((Order)order2)->hour){
 return -1;
 } else{
 TechnionFaculty Faculty1= getFacultyOfCompany(((Order)order1)->company);
 TechnionFaculty Faculty2= getFacultyOfCompany(((Order)order2)->company);
 if (Faculty1 > Faculty2){
 return 1;
 }else if (Faculty1 < Faculty2){
 return -1;
 }else{
 if (((Order)order1)->room_id >((Order)order2)->room_id){
 return 1;
 }else if (((Order)order1)->room_id < ((Order)order2)->room_id){
 return -1;
 }else{
 return 0;
 }
 }
 }
 }
 
 bool orderEqualsRoom(Order order1, Order order2) {
 assert(order1 && order2);
 return order1->time == order2->time &&
 order1->room_id == order2->room_id;
 }
 
 int orderEqualsEscaper(Order order1, Order order2 ){
 assert(order1 && order2);
 return strcmp(getEmailEscaper(order1->escaper),
 getEmailEscaper(order2->escaper));
 }
 
 int getPriceOrder(Order order){
 assert(order);
 return order->tot_price;
 }
 
 void putPriceOrder(Order* order,int tot_p){
 (*order)->tot_price =tot_p;
 }
 
 char* getTimeOrder(Order order) {
 assert(order);
 return order->time;
 }
 
 int getHourOrder(Order order) {
 assert(order);
 return order->hour;
 }
 
 int getNumPOrder(Order order) {
 assert(order);
 return order->num_ppl;
 }
 
 int getRoomIdOrder(Order order) {
 assert(order);
 return order->room_id;
 }
 
 Escaper getEscaperOrder(Order order) {
 assert(order);
 return order->escaper;
 }
 
 Company getCompanyOrder(Order order) {
 assert(order);
 return order->company;
 }
 
 int getDayOrder(Order order){
 assert(order);
 return order->day;
 }

 
 */
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
