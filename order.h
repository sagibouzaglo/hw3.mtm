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

typedef struct order* Order;

typedef enum {

} OrderResult;

/** Allocates a new order */
Order orderCreate(int time, Escaper* escaper, int num_ppl, Company* company, int room_id);
 
/** Frees an existing order object */
void orderDestroy(Order order);
 

#endif /* order_h */
