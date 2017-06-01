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

struct order {
    int time;
    Escaper escaper;
    int num_ppl;
    int room_id;
    Company compeny;
    int tot_price;
};


/** Allocates a new order */
Order orderCreate(int time, Escaper escaper, int num_ppl, Company company, int room_id){
    if (!escaper || !company) {
        return NULL;
    }
    Order order = malloc(sizeof(*order));
    if (!order) {
        return NULL;
    }
    order->compeny=company;
    order->time = time;
    order->escaper=escaper;
    order->num_ppl = num_ppl;
    order->room_id=room_id;
    order->tot_price=0;
    return order;
}

/** Frees an existing order object */
void orderDestroy(Order order){
    free(order);
}

/** Allocates a new order which is a copy of the argument */
Order  orderCopy(Order order){
    if (!order) {
        return NULL;
    }
    return orderCreate(order->time, order->escaper ,order->num_ppl,order->compeny ,order->room_id );
}
/** Returns true if both room orders and time are identical */
bool orderEqualsRoom(Order order1, Order order2) {
    assert(order1 && order2);
    return order1->time == order2->time &&
           order1->room_id == order2->room_id;
}
/** Returns true if both Escaper order and time are identical */
bool orderEqualsEscaper(Order order1, Order order2) {
    assert(order1 && order2);
    return order1->time == order2->time &&
            order1->escaper == order2->escaper;
}
int getTimeOrder(Order order){
    if(!order){
        return NULL;
    }
    return order->time;
}
int getNumPOrder(Order order){
    if(!order){
        return NULL;
    }
    return order->num_ppl;
}
int getRoomIdOrder(Order order){
    if(!order){
        return NULL;
    }
    return order->room_id;
}
Escaper getEscaperOrder(Order order){
    if(!order){
        return NULL;
    }
    return order->escaper;
}
Company getCompanyOrder(Order order){
    if(!order){
        return NULL;
    }
    return order->compeny;
}
void PayToFaculty(Escaper escaper,Room room,int* profitFaculty, int num_ppl){
    assert(escaper && profitFaculty);

}