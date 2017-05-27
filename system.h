//
//  system.h
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef system_h
#define system_h

#include <stdio.h>
#include "mtm_ex3.h"
#include "set.h"
#include "list.h"
#include <stdio.h>


struct system {
    int day;
    Set company;
    Set escaper;
    List orders;
    int profit[UNKNOWN];
};

/*
 
 */
int create_system();


/*
 
 */
int destroy_system();

/*
 
 */
int system_add_company();

/*
 
 */
int system_remove_company();

/*
 
 */
int system_add_room();

/*
 
 */
int system_remove_room();

/*
 
 */
int system_add_escaper();

/*
 
 */
int system_remove_escaper();

/*
 
 */
int system_add_order();

/*
 
 */
int system_day();

/*
 
 */
int system_best_faculty();


#endif /* system_h */
