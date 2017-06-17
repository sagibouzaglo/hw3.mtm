//
//  order.c
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "order.h"
#include "list.h"

#define AFTER_DISCOUNT 0.75
#define HOURS_DAY 23

static int findAndgetPriceRoom(Company company,int roomId);
static int CalculatePrice(int priseRoom , int num_ppl, Order order);
static bool hourOrder (char* time, Order order);


struct order {
    char* time;
    int day;
    int hour;
    Escaper escaper;
    int num_ppl;
    int room_id;
    Company company;
    int tot_price;
};



/** Allocates a new order */
Order orderCreate(char* time, Escaper escaper, int num_ppl, Company company1, int room_id,OrderReturn* Result){

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
    order->tot_price=CalculatePrice(findAndgetPriceRoom(company1,room_id),num_ppl, order);
    return order;
}

/** Frees an existing order object */
void orderDestroy(void* order){
    if(!order) return;
    free(((Order)order)->time);
    free(order);
}

/** 
    Allocates a new order which is a copy of the argument
    errors:
    NULL - order is null
    
 */
ListElement orderCopy(void* order){
    assert(order);
    OrderReturn Result=ORD_SUCCESS;
    return orderCreate(((Order)order)->time, ((Order)order)->escaper ,((Order)order)->num_ppl,
                       ((Order)order)->company ,((Order)order)->room_id ,&Result);
}

int compareOrders(void* order1,void* order2){
    if (((Order)order1)->hour > ((Order)order2)->hour){
        return 1;
    } else if (((Order)order1)->hour < ((Order)order2)->hour){
        return -1;
    } else{
        TechnionFaculty Faculty1 = getFacultyOfCompany(((Order)order1)->company);
        TechnionFaculty Faculty2 = getFacultyOfCompany(((Order)order2)->company);
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
/**
    Returns true if both room orders and time are identical
 */
bool orderEqualsRoom(Order order1, Order order2) {
    assert(order1 && order2);
    return order1->time == order2->time &&
            order1->room_id == order2->room_id;
}

/** 
    Returns true if both Escaper order and time are identical
 */
int orderEqualsEscaper(Order order1, Order order2 ){
    assert(order1 && order2);
    return strcmp(getEmailEscaper(order1->escaper),getEmailEscaper(order2->escaper));
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

static bool hourOrder (char* time, Order order){
    for(int i=0;i<strlen(time);++i){
        if(*(time + i) == '-'){
            *(time+i) = 0;
            order->day=atol(time);
            ++i;
            order->hour=atol(time+i);
            break;
        }
    }
    if(order->day<0 || order->hour <0 || order->hour >HOURS_DAY ){
        order->hour=0;
        order->day=0;
        return false;
    }
    return true;
}
static int CalculatePrice(int priseRoom , int num_ppl, Order order) {
    assert(order);
    Company company = getCompanyOrder(order);
    if(!company) return 0;
    TechnionFaculty faculty = getFacultyOfCompany(company);
    Escaper escaper1 = getEscaperOrder(order);
    TechnionFaculty faculty2=getFacultyEscaper(escaper1);
    if(faculty == faculty2){
        return ((int)(num_ppl*priseRoom*AFTER_DISCOUNT));
    } else {
        return (num_ppl * priseRoom);
    }
}
static int findAndgetPriceRoom(Company company,int roomId){
    assert(company);
    Set rooms = getCompanyRooms(company);
    if(!rooms || !setGetSize(rooms)) return 0;


    SET_FOREACH( Room , roomOfCompany ,rooms){
        if(getIdRoom(roomOfCompany)==roomId){
            return getPriceRoom(roomOfCompany);
        }
    }

    return 0;
}
