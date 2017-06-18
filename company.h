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


/**
 * Allocates a new company,intialize it and return a pointer to the company
 *
 * @param email - the company email .
 * @param faculty - the company faculty.
 * @param Result - hold the result value.
 *
 * @return result
 * COM_NULL_PARAMETER - one of the  sent pointers is NULL.
 * COM_OUT_OF_MEMORY - allocation failed.
 * COM_SUCCESS - company created seccesfully.
 *
 * @return
 * pointer to the new company
 */
Company companyCreate(char* email, TechnionFaculty faculty, CompanyReturn* Result);

/**
 * free all allocated memory for the company
 *
 * @param company -  pointer to the company.
 */
void companyDestroy(void* company);

/**
 * Allocates a new company,and copy to it the sent company
 *
 * @param company - the company we want to copy.
 *
 * @return result
 * COM_NULL_PARAMETER - one of the  sent pointers is NULL.
 * COM_OUT_OF_MEMORY - allocation failed.
 * COM_SUCCESS - company created seccesfully.
 *
 * @return
 * pointer to the new company
 */
SetElement companyCopy(void* company);

/**
 * gets 2 companys and compare their names.
 *
 * @param company1 - pointer to the first checked company.
 * @param company2 - pointer to the second checked company.
 *
 * @return
 * 1 - company1 is first.
 * 0 - the companys are equal.
 * -1 - company2 is first.
 */

int companyCompare(void* company1, void* company2);

/**
 * gets the email of the sent company
 *
 * @param company - a pointer to a company.
 *
 * @return
 * emailReturn - the company email.
 */
char* getEmailCompany(Company company);

/**
 * gets the faculty of the sent company
 *
 * @param company - a pointer to a company.
 *
 * @return
 * company->Faculty - the company faculty.
 */
TechnionFaculty getFacultyOfCompany(Company company);

/**
 * gets the set of rooms of the sent company
 *
 * @param company - a pointer to a company.
 *
 * @return
 * company->rooms -set of room owned by the sent company.
 */
Set getCompanyRooms(Company company);

#endif /* COMPANY_H */

