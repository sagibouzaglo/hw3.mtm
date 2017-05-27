//
//  order.c
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "order.h"

struct order {
    int time;
    Escaper* escaper;
    int num_ppl;
    int room_id;
    Company* compeny;
};


