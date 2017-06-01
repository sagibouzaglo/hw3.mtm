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

typedef struct order* Order;


/** Allocates a new order */
Order orderCreate(int time, Escaper escaper, int num_ppl, Company company, int room_id);

/** Frees an existing order object */
void orderDestroy(Order order);

/** Allocates a new date which is a copy of the argument */
Order  orderCopy(Order order);

/** Returns true if both room orders and time are identical */
bool orderEqualsRoom(Order order1, Order order2);
}
/** Returns true if both Escaper order and time are identical */
bool orderEqualsEscaper(Order order1, Order order2) ;

#endif /* order_h */
