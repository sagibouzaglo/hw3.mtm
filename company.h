//
//  company.h
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef company_h
#define company_h

#include "order.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
#include <string.h>

#include <stdio.h>
typedef struct company* Company;


/** Allocates a new company */
Company companyCreate(char* email, TechnionFaculty faculty);

/** Frees an existing company object */
void companyDestroy(void* company);

/** Allocates a new company which is a copy of the argument */
void* companyCopy(void* company);

/** Returns true if both email company are identical */
int companyCompare(void* company1, void* company2);

char* getEmailCompany(Company company);

TechnionFaculty getFacultyOfCompuny(Company company);

#endif /* company_h */

