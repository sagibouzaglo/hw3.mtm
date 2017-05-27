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
    int profit[(((int)UNKNOWN)+1)];
};

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
