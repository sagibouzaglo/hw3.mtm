//
//  escaper.h
//  hw3
//
//  Created by sagi bouzaglo on 28/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef escaper_h
#define escaper_h

//#include "company.h"
//#include "order.h"

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "mtm_ex3.h"

typedef enum {
    Esc_OUT_OF_MEMORY, // You should exit program after this error
    Esc_NULL_PARAMETER,
    Esc_INVALID_PARAMETER,
    Esc_SUCCESS,
} EscaperReturn;

typedef struct escaper* Escaper;

/**
 * Adds a new escaper to the escapers set and allocate the memory for it and
 *
 * @param email -  the escaper email.
 * @param faculty - the escaper faculty.
 * @param skill_level - the escaper skill level.
 * @param Result  - holds the 
 *
 * @return
 * Esc_OUT_OF_MEMORY -  if memory allocated faild.
 * Esc_NULL_PARAMETER - if NULL sent to the function.
 * Esc_INVALID_PARAMETER - if the sent parameters were invalid.
 * Esc_SUCCESS -  the eascaper added successfully.
 */
Escaper escaperCreate(char* email, TechnionFaculty faculty ,
                                        int skill_level,EscaperReturn* Result);

/**
 * remove the sent escaper from the escapers set and deallocate 
 * the memory for it and
 *
 * @param escaper -  the escaper we want to remove.
 */

void escaperDestroy(void* escaper);

/**
 * Allocates a new escaper and copy the sent escaper
 *
 * @param escaper -  the escaper we want to copy.
 *
 * @return
 * Esc_OUT_OF_MEMORY -  if memory allocated faild.
 * Esc_NULL_PARAMETER - if NULL sent to the function.
 * Esc_INVALID_PARAMETER - if the sent parameters were invalid.
 * Esc_SUCCESS -  the eascaper added successfully.
 */
void* escaperCopy(void* escaper);

/**
 * compare two escapers and return true if both escapers have the same email.
 *
 * @param escaper1 -  the first escaper.
 * @param escaper2 -  the second escaper.
 *
 * @return
 * 0 - id emails are identical.
 */
int escaperEquals(void* escaper1, void* escaper2);

/**
 * allocate a string for the escaper email and copy it
 *
 * @param escaper -  the escaper we want to copy his email.
 *
 * @return
 * emailReturn - the new email.
 */
char* getEmailEscaper(Escaper escaper);

/**
 * recieve an escaper and return his skill level
 *
 * @param escaper -  the escaper we want his skill level.
 *
 * @return
 * skill_level - the escaper skill level.
 */
int getSkillLevel(Escaper escaper);

/**
 * recieve an escaper and return his Faculty
 *
 * @param escaper -  the escaper we want to copy.
 *
 * @return
 * Faculty - the escaper faculty.
 */
TechnionFaculty getFacultyEscaper(Escaper escaper);

/**
 * check if the escaper email is valid
 *
 * @param email -  the escaper email.
 *
 * @return
 * true - the email is valid.
 * false - the email is invalid.
 */
bool IfEscaperEmailValid(char* email);

#endif /* escaper_h */
