#ifndef COMPANY_H
#define COMPANY_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//#include "order.h"
#include "room.h"
#include "set.h"
#include "mtm_ex3.h"

typedef enum {
    COM_OUT_OF_MEMORY, // You should exit program after this error
    COM_NULL_PARAMETER,
    COM_SUCCESS,
} CompanyReturn;

typedef struct company_t* Company;


/** Allocates a new company */
SetElement companyCreate(char* email, TechnionFaculty faculty, CompanyReturn* Result);

/** Frees an existing company object */
void companyDestroy(void* company);

/** Allocates a new company which is a copy of the argument */
SetElement companyCopy(void* company);

/** Returns true if both email company are identical */
int companyCompare(void* company1, void* company2);

char* getEmailCompany(Company company);

TechnionFaculty getFacultyOfCompany(Company company);

Set getCompanyRooms(Company company);

#endif /* COMPANY_H */

