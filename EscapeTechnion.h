//
//  EscapeTechnion.h
//  hw3
//
//  Created by sagi bouzaglo on 28/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef EscapeTechnion_h
#define EscapeTechnion_h

#include <stdlib.h>
#include <stdio.h>
#include "mtm_ex3.h"
#include "set.h"
#include "list.h"
#include "company.h"
#include "room.h"
#include "order.h"
#include "escaper.h"

typedef struct escapetechnion* EscapeTechnion;

/**
 * Allocates a new EscapeTechnion system and intialize it
 *
 * @param EscapeTechnion - a pointer to the system adt.
 *
 * @return result
 * MTM_OUT_OF_MEMORY - allocation failed.
 * MTM_SUCCESS - EscapeTechnion system created seccesfully.
 */
MtmErrorCode create_EscapeTechnion(EscapeTechnion *EscapeTechnion);

/**
 * free all allocated memory for the EscapeTechnion system
 *
 * @param EscapeTechnion -  the system ADT.
 */
void destroy_EscapeTechnion(EscapeTechnion EscapeTechnion);

/**
 *  allocate new company and add it to the company set.
 *
 * @param email -  the company email.
 * @param EscapeTechnion -  the system ADT.
 * @param faculty -  the company faculty.
 *
 * @return result
 * MTM_NULL_PARAMETER - one of the sent pointers is NULL.
 * MTM_OUT_OF_MEMORY - allocation failed.
 * MTM_EMAIL_ALREADY_EXISTS - company email already exist.
 * MTM_SUCCESS - company copied seccesfully.
 */
MtmErrorCode EscapeTechnion_add_company(char* email,EscapeTechnion EscapeTechnion, TechnionFaculty faculty);

/**
 *  the function search the company match the recieved mail and remove it from
 *  the set of companies.
 *  the function add the company earning of the day to the faculty earnings
 *  and free all memory allocated for the company.
 *
 * @param email -  the company email.
 * @param EscapeTechnion -  the system ADT.
 *
 * @return result
 * MTM_NULL_PARAMETER - one of the sent pointers is NULL.
 * MTM_COMPANY_EMAIL_DOES_NOT_EXIST - the company mail doesn't exist.
 * MTM_RESERVATION_EXISTS - there is a reservation for the room.
 * MTM_SUCCESS - company removed seccesfully.
 */
MtmErrorCode EscapeTechnion_remove_company(char* email,EscapeTechnion EscapeTechnion);

/**
 *  The function allocate new room and add it to the room set.
 *
 * @param email - the email of the company owns the room.
 * @param id - the room id.
 * @param price -  the price for orderinf the room.
 * @param num_ppl -  the recommended number of people for the room.
 * @param working_hour -  the room working hours.
 * @param difficulty -  the room difficulty.
 * @param EscapeTechnion -  the system ADT.
 *
 * @return result
 * MTM_NULL_PARAMETER - one of the sent pointers is NULL.
 * MTM_COMPANY_EMAIL_DOES_NOT_EXIST - the  mail sent is NULL.
 * MTM_ID_ALREADY_EXIST - the sent id already exist.
 * MTM_SUCCESS - room added created seccesfully.
 */
MtmErrorCode EscapeTechnion_add_room(char* email,int id, int price, int num_ppl,
                                     char* working_hour, int difficulty,
                                     EscapeTechnion EscapeTechnion);

/**
 *  The function check if there are open reservation to the room.
 * if not, the room will be removed and all the allocated memory will free.
 *
 * @param faculty - the faculty of the company owns the room.
 * @param id - the room id.
 * @param EscapeTechnion -  the system ADT.
 *
 * @return result
 * MTM_NULL_PARAMETER - one of the sent pointers is NULL.
 * MTM_ID_DOES_NOT_EXIST - the sent room id doesn't exist.
 * MTM_RESERVATION_EXISTS - there is a reservation for the room we want to remove.
 * MTM_SUCCESS -   room removed seccesfully.
 */
MtmErrorCode EscapeTechnion_remove_room(TechnionFaculty faculty, int id,
                                        EscapeTechnion EscapeTechnion);

/**
 *  The function allocate new escaper and add it to the escaper set.
 *
 * @param email - the email of the escaper.
 * @param faculty - the escaper faculty.
 * @param skill_level -  the escaper skill level.
 * @param EscapeTechnion -  the system ADT.
 *
 * @return result
 * MTM_NULL_PARAMETER - one of the sent pointers is NULL.
 * MTM_CLIENT_EMAIL_DOES_NOT_EXIST - the mail sent is already exist for other escaper.
 * MTM_SUCCESS - EscapeTechnion system created seccesfully.
 */
MtmErrorCode EscapeTechnion_add_escaper(char* email,
                                        TechnionFaculty faculty,int skill_level,
                                        EscapeTechnion EscapeTechnion);

/**
 *  The function check if there are open reservation to the room.
 * if not, the room will be removed and all the allocated memory will free.
 *
 * @param email - the escaper email.
 * @param EscapeTechnion -  the system ADT.
 *
 * @return result
 * MTM_INVALID_PARAMETER - one of the sent pointers is NULL.
 * MTM_CLIENT_EMAIL_DOES_NOT_EXIST - the mail sent is already exist for other escaper.
 * MTM_SUCCESS - EscapeTechnion system created seccesfully.
 */
MtmErrorCode EscapeTechnion_remove_escaper(char* email,EscapeTechnion EscapeTechnion);

/**
 *  creates a new order for a room and calculate the price based on the .
 *
 * @param email - the email of the escaper.
 * @param faculty - the company owns the room faculty.
 * @param id - the room id.
 * @param time - the day and hour of the order.
 * @param num_ppl - the number of people ordering the room.
 * @param EscapeTechnion -  the system ADT.
 *
 * @return result
 * MTM_INVALID_PARAMETER - one of the sent pointers is NULL.
 * MTM_CLIENT_EMAIL_DOES_NOT_EXIST - the mail sent doesn't match any escaper.
 * MTM_ID_DOES_NOT_EXIST - the id sent doesn't match any room.
 * MTM_OUT_OF_MEMORY - allocation failed.
 * MTM_NO_ROOMS_AVAILABLE - there are no rooms available.
 * MTM_CLIENT_IN_ROOM - escaper have another order for the same day and hour.
 * MTM_ROOM_NOT_AVAILABLE - the asked room is unavailable.
 * MTM_SUCCESS - EscapeTechnion system created seccesfully.
 */
MtmErrorCode EscapeTechnion_add_escaper_order(char* email,TechnionFaculty faculty,
                                              int id,char* time, int num_ppl,
                                              EscapeTechnion EscapeTechnion);

/**
 *  prints all the orders made that day by their time, and faculty id.
 * advance system day.
 *
 * @param output - the output channel.
 * @param EscapeTechnion -  the system ADT.
 *
 * @return result
 * MTM_INVALID_PARAMETER - one of the sent pointers is NULL.
 * MTM_OUT_OF_MEMORY - allocation failed.
 * MTM_SUCCESS - EscapeTechnion system created seccesfully.
 */
MtmErrorCode technion_report_day(FILE* output,EscapeTechnion EscapeTechnion);

/**
 *  prints 3 faculties that gained the most profit.
 *
 * @param output - the output channel.
 * @param EscapeTechnion -  the system ADT.
 *
 * @return result
 * MTM_INVALID_PARAMETER - one of the sent pointers is NULL.
 * MTM_OUT_OF_MEMORY - allocation failed.
 * MTM_SUCCESS - EscapeTechnion system created seccesfully.
 */
MtmErrorCode technion_report_best(FILE *output,EscapeTechnion EscapeTechnion);

/**
 * calculate the available recommended room and create an order for it
 *
 * @param email - the escaper email .
 * @param num_ppl - the number of people ordering the room.
 * @param escapeTechnion -  the system ADT.
 *
 * @return result
 * MTM_INVALID_PARAMETER - one of the sent pointers is NULL.
 * MTM_OUT_OF_MEMORY - allocation failed.
 * MTM_NO_ROOMS_AVAILABLE - no rooms available.
 * MTM_SUCCESS - EscapeTechnion system created seccesfully.
 */
MtmErrorCode EscapeTechnion_add_escaper_recommend(char* email, int num_ppl, EscapeTechnion escapeTechnion);

#endif /* EscapeTechnion_h */
