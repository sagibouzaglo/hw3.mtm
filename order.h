//
//  order.h
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef order_h
#define order_h
#include <stdio.h>
#include "mtm_ex3.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "company.h"
#include "escaper.h"

typedef enum {
    ORD_OUT_OF_MEMORY, // You should exit program after this error
    ORD_INVALID_COMMAND_LINE_PARAMETERS, // You should exit program after this error
    ORD_CANNOT_OPEN_FILE, // You should exit program after this error
    ORD_NULL_PARAMETER,
    ORD_INVALID_PARAMETER,
    ORD_EMAIL_ALREADY_EXISTS,
    ORD_COMPANY_EMAIL_DOES_NOT_EXIST,
    ORD_CLIENT_EMAIL_DOES_NOT_EXIST,
    ORD_ID_ALREADY_EXIST,
    ORD_ID_DOES_NOT_EXIST,
    ORD_CLIENT_IN_ROOM,
    ORD_ROOM_NOT_AVAILABLE,
    ORD_RESERVATION_EXISTS,
    ORD_NO_ROOMS_AVAILABLE,
    ORD_SUCCESS,
} OrderReturn;

typedef struct order* Order;


/** Allocates a new order */
Order orderCreate(int time, Escaper escaper, int num_ppl, Company company, int room_id,OrderReturn* Result);

/** Frees an existing order object */
void orderDestroy(void* order);

/** Allocates a new date which is a copy of the argument */
void*  orderCopy(void* order);

/** Returns true if both room orders and time are identical */
bool orderEqualsRoom(Order order1, Order order2);

/** Returns true if both Escaper order and time are identical */
int orderEqualsEscaper(Order order1, Order order2 ,EscaperReturn* Result);

int getPriceOrder(Order order);

int getTimeOrder(Order order);

int getNumPOrder(Order order);

int getRoomIdOrder(Order order);

Escaper getEscaperOrder(Order order);

Company getCompanyOrder(Order order);

#endif /* order_h */
