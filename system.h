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
#include <stdlib.h>


typedef struct system* System;

/*
 
 */
int create_system();

/*
 
 */
int destroy_system();

/*
    Recieve 2 arguments:
    email - the company email.
    faculty - the faculty the company belong to.
    
    The function allocate new company and add it.
    
    Errors:
    MTM_INVALID_PARAMETER
    MTM_EMAIL_ALREADY_EXISTS
 */
int system_add_company();

/*
    Recieve 1 argument:
    email - the company email.
 
    the function search the company match the recieved mail and remove it from 
    the set of companies.
    the function add the company earning of the day to the faculty earnings
    and free all memory allocated for the company.
 
    errors:
    MTM_INVALID_PARAMETER
    MTM_COMPANY_EMAIL_DOES_NOT_EXIST
    MTM_RESERVATION_EXISTS
 */
int system_remove_company();

/*
 Recieve 6 arguments:
 email - the company email.
 id - the id of the room.
 price - price per person, multiplier of 4.
 num_ppl - reccomended people in the room.
 working_hours - xx-yy, xx- opening hours, yy - closing hours.
 difficulty - difficulty of the room, from 1-10.
 
 The function allocate new room and add it to the set rooms.
 
 Errors:
 MTM_INVALID_PARAMETER
 MTM_COMPANY_EMAIL_DOES_NOT_EXIST
 MTM_ID_ALREADY_EXISTS
 */
int system_add_room();

/*
 Recieve 2 argument:
 faculty - the faculty the room belong to.
 id - room id.
 
 The function check if there are open reservation to the room.
 if not, the room will be removed and all the allocated memory will free.
 errors:
 MTM_INVALID_PARAMETER
 MTM_ID_DOES_NOT_EXIST
 MTM_RESERVATION_EXISTS
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
