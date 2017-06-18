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
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "mtm_ex3.h"
#include "escaper.h"
#include "room.h"
#include "list.h"

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

/**
 * Allocates a new order,intialize it and return a pointer to the order
 *
 * @param time - time of day we want to order the room.
 * @param escaper - the escaper that ordered the room .
 * @param num_ppl - the number of people for the order.
 * @param company1 the company owns the room.
 * @param room_id - id of the room we want to order.
 * @param Result - holds the result sent back.
 *
 * @return result
 * ORD_NULL_PARAMETER - one of the  sent pointers is NULL.
 * ORD_OUT_OF_MEMORY - allocation failed.
 * ORD_SUCCESS - order created seccesfully.
 *
 * @return
 * pointer to the new order
 */
Order orderCreate(char* time, Escaper escaper, int num_ppl, Company company1,
                  int room_id,OrderReturn* Result);

/**
 * free all allocated memory for the order
 *
 * @param order -  pointer to the order.
 */
void orderDestroy(void* order);

/**
 * Allocates a new order,and copy the sent order to it
 *
 * @param order - the order we want to copy.
 *
 * @return result
 * ORD_NULL_PARAMETER - one of the  sent pointers is NULL.
 * ORD_OUT_OF_MEMORY - allocation failed.
 * ORD_SUCCESS - order created seccesfully.
 *
 * @return
 * pointer to the new order
 */
ListElement orderCopy(void* order);

/**
 * check if both room orders and time are identical
 *
 * @param order1 - pointer to the first checked order.
 * @param order2 - pointer to the second checked order.
 *
 * @return
 * true - the orders are identical.
 * false - the ordeers are different.
 */
bool orderEqualsRoom(Order order1, Order order2);

/**
 * check if both Escaper order and time are identical
 *
 * @param order1 - pointer to the first checked order.
 * @param order2 - pointer to the second checked order.
 *
 * @return
 * true - the orders are identical.
 * false - the ordeers are different.
 */
int orderEqualsEscaper(Order order1, Order order2);

/**
 * gets the price of the sent order
 *
 * @param order - a pointer to a room.
 *
 * @return
 * order->tot_price - the order price.
 */
int getPriceOrder(Order order);

/**
 * gets the time of the sent order
 *
 * @param order - a pointer to a order.
 *
 * @return
 * order->time - the order time.
 */
char* getTimeOrder(Order order);

/**
 * gets the number of people of the sent order
 *
 * @param order - a pointer to a order.
 *
 * @return
 * order->num_ppl - the number of people ordering the room.
 */
int getNumPOrder(Order order);

/**
 * gets the id of the ordered room
 *
 * @param order - a pointer to a order.
 *
 * @return
 * order->room_id - the ordered room id.
 */
int getRoomIdOrder(Order order);

/**
 * gets the escaper that ordered the room
 *
 * @param order - a pointer to a order.
 *
 * @return
 * order->escaper - the escaper that made the order.
 */
Escaper getEscaperOrder(Order order);

/**
 * gets the company owns the ordered room
 *
 * @param order - a pointer to a order.
 *
 * @return
 * order->company - the company owns the ordered room.
 */
Company getCompanyOrder(Order order);

/**
 * put tot_p in the order total price
 *
 * @param order - a pointer to a order.
 * @paran tot_p - the total price
 */
void putPriceOrder(Order* order,int tot_p);

/**
 * gets the day of order
 *
 * @param order - a pointer to a order.
 *
 * @return
 * order->day - the day of order .
 */
int getDayOrder(Order order);

/**
 * gets the price of the sent room
 *
 * @param order - a pointer to a order.
 *
 * @return
 * order->hour - the room price.
 */
int getHourOrder(Order order);

/**
 * compare orders by hour, if hours are equal than by
 * faculty and if faculty is equal than by room id.
 *
 * @param order1 - pointer to the first checked order.
 * @param order2 - pointer to the second checked order.
 *
 * @return
 * 1 - order1 is first.
 * 0 - the orders are equal.
 * -1 - oreder2 is first.
 */
int compareOrders(void* order1,void* order2);


#endif /* order_h */
