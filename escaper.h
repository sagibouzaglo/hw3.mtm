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
#include "escaper.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include <stdio.h>
typedef struct escaper* Escaper;

/** Allocates a new escaper */
Escaper escaperCreate(char* email, TechnionFaculty faculty , int skill_level);

/** Frees an existing escaper object */
void escaperDestroy(Escaper escaper);

/** Allocates a new escaper which is a copy of the argument */
Escaper escaperCopy(Escaper escaper);

/** Returns true if both email escaper are identical */
bool escaperEquals(Escaper escaper1, Escaper escaper2);

char* getEmailEscaper(Escaper escaper);

int getSkillLevel(Escaper escaper);

TechnionFaculty getFacultyEscaper(Escaper escaper);

#endif /* escaper_h */
