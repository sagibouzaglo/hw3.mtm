//
//  order.c
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "order.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "company.h"
#include "escaper.h"
#include "room.h"
#define AFTER_DISCOUNT 0.75
#define HOURS_DAY 23

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
Order orderCreate(char* time, Escaper escaper, int num_ppl, Company company, int room_id,OrderReturn* Result){
    if (!escaper || !company) {
        *Result= ORD_NULL_PARAMETER;
        return NULL;
    }
    Order order = malloc(sizeof(*order));
    if (!order) {
        *Result= ORD_OUT_OF_MEMORY;
        return NULL;
    }
    order->time=malloc((sizeof(char)*strlen(time))+1);
    if(!order->time){
        return NULL;
    }
    order->company=company;
    strcmp(time,order->time);
    order->escaper=escaper;
    order->num_ppl = num_ppl;
    order->room_id=room_id;
    order->tot_price=0;
    return order;
}

/** Frees an existing order object */
void orderDestroy(void* order){
    free(order);
}

/** 
    Allocates a new order which is a copy of the argument
    errors:
    NULL - order is null
    
 */
void*  orderCopy(void* order){
    assert(order);
    OrderReturn Result;
    return orderCreate(((Order)order)->time, ((Order)order)->escaper ,((Order)order)->num_ppl,
                       ((Order)order)->company ,((Order)order)->room_id ,&Result);
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
int orderEqualsEscaper(Order order1, Order order2 ,EscaperReturn* Result){
    assert(order1 && order2);
    return strcmp(getEmailEscaper(order1->escaper,Result),getEmailEscaper(order1->escaper,Result));
}

int getPriceOrder(Order order){
    if (!order) {
        return NULL;
    }
    return order->tot_price;
}

char* getTimeOrder(Order order) {
        if (!order) {
            return NULL;
        }
        return order->time;
    }
int getNumPOrder(Order order) {
        if (!order) {
            return NULL;
        }
        return order->num_ppl;
    }
int getRoomIdOrder(Order order) {
        if (!order) {
            return NULL;
        }
        return order->room_id;
    }
Escaper getEscaperOrder(Order order) {
        if (!order) {
            return NULL;
        }
        return order->escaper;
    }
Company getCompanyOrder(Order order) {
        if (!order) {
            return NULL;
        }
        return order->company;
    }

static bool hourOrder (char* time, Order order){
    assert(room && working_hour);
    for(int i=0;i<strlen(time);++i){
        if(*(time + i) == '-'){
            *(time+i)=NULL;
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


