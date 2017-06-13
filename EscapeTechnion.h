//
//  EscapeTechnion.h
//  hw3
//
//  Created by sagi bouzaglo on 28/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef EscapeTechnion_h
#define EscapeTechnion_h

#include <stdio.h>
#include "mtm_ex3.h"
#include "set.h"
#include "list.h"
#include <stdlib.h>


typedef struct escapetechnion* EscapeTechnion;

/*

 */
MtmErrorCode create_EscapeTechnion(EscapeTechnion *EscapeTechnion);

/*

 */
MtmErrorCode destroy_EscapeTechnion(EscapeTechnion *EscapeTechnion);

/*
    Recieve 2 arguments:
    email - the company email.
    faculty - the faculty the company belong to.

    The function allocate new company and add it.

    Errors:
    MTM_INVALID_PARAMETER
    MTM_EMAIL_ALREADY_EXISTS
 */
MtmErrorCode EscapeTechnion_add_company(char* email,EscapeTechnion *EscapeTechnion, TechnionFaculty faculty);

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
MtmErrorCode EscapeTechnion_remove_company(char* email,EscapeTechnion *EscapeTechnion);

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
MtmErrorCode EscapeTechnion_add_room(char* email,int id, int price, int num_ppl,
                                     char* working_hour, int difficulty,
                                     EscapeTechnion *EscapeTechnion);

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
MtmErrorCode EscapeTechnion_remove_room(TechnionFaculty faculty, int id,
                                        EscapeTechnion *EscapeTechnion);

/*

 */
MtmErrorCode EscapeTechnion_add_escaper(char* email,
                                        TechnionFaculty faculty,int skill_level,
                                        EscapeTechnion *EscapeTechnion);

/*

 */
MtmErrorCode EscapeTechnion_remove_escaper(char* email,EscapeTechnion *EscapeTechnion);

/*

 */
MtmErrorCode EscapeTechnion_add_order(char* email,TechnionFaculty faculty, int id,int time, int num_ppl,
                                      EscapeTechnion *EscapeTechnion);

/*

 */
MtmErrorCode EscapeTechnion_day();

/*

 */
MtmErrorCode EscapeTechnion_best_faculty();

/**
 
 */
MtmErrorCode technion_report_day(FILE* output,EscapeTechnion EscapeTechnion);

/**
 
 */
MtmErrorCode technion_report_best(EscapeTechnion *EscapeTechnion);



#endif /* EscapeTechnion_h */
