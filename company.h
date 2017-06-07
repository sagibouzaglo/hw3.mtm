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

typedef enum {
    COM_OUT_OF_MEMORY, // You should exit program after this error
    COM_INVALID_COMMAND_LINE_PARAMETERS, // You should exit program after this error
    COM_CANNOT_OPEN_FILE, // You should exit program after this error
    COM_NULL_PARAMETER,
    COM_INVALID_PARAMETER,
    COM_EMAIL_ALREADY_EXISTS,
    COM_COMPANY_EMAIL_DOES_NOT_EXIST,
    COM_SUCCESS,
} CompanyReturn;

typedef struct company* Company;


/** Allocates a new company */
Company companyCreate(char* email, TechnionFaculty faculty, CompanyReturn Result);

/** Frees an existing company object */
void companyDestroy(void* company,CompanyReturn Result);

/** Allocates a new company which is a copy of the argument */
void* companyCopy(void* company,CompanyReturn Result);

/** Returns true if both email company are identical */
int companyCompare(void* company1, void* company2,CompanyReturn Result);

char* getEmailCompany(Company company,CompanyReturn Result);

TechnionFaculty getFacultyOfCompuny(Company company,CompanyReturn Result);

bool IfEmailValid(char* email);
#endif /* company_h */

