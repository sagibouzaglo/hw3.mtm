//
//  escaper.h
//  hw3
//
//  Created by sagi bouzaglo on 28/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef escaper_h
#define escaper_h

#include "company.h"
#include "order.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

typedef enum {
    Esc_OUT_OF_MEMORY, // You should exit program after this error
    Esc_NULL_PARAMETER,
    Esc_INVALID_PARAMETER,
    Esc_EMAIL_ALREADY_EXISTS,
    Esc_COMPANY_EMAIL_DOES_NOT_EXIST,
    Esc_CLIENT_EMAIL_DOES_NOT_EXIST,
    Esc_ID_ALREADY_EXIST,
    Esc_ID_DOES_NOT_EXIST,
    Esc_CLIENT_IN_ROOM,
    Esc_ROOM_NOT_AVAILABLE,
    Esc_RESERVATION_EXISTS,
    Esc_NO_ROOMS_AVAILABLE,
    Esc_SUCCESS,
} EscaperReturn;

typedef struct escaper* Escaper;

/** Allocates a new escaper */
Escaper escaperCreate(char* email, TechnionFaculty faculty , int skill_level,EscaperReturn* Result);

/** Frees an existing escaper object */
void escaperDestroy(void* escaper);

/** Allocates a new escaper which is a copy of the argument */
void* escaperCopy(void* escaper);

/** Returns true if both email escaper are identical */
int escaperEquals(void* escaper1, void* escaper2);

char* getEmailEscaper(Escaper escaper,EscaperReturn* Result);

int getSkillLevel(Escaper escaper);

TechnionFaculty getFacultyEscaper(Escaper escaper);

bool IfEmailValid(char* email);
#endif /* escaper_h */
