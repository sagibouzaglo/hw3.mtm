//
//  company.c
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//


#include "company.h"
#include "order.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
#include <string.h>


struct company {
    char* email;
    TechnionFaculty Faculty;
    Set rooms;
};


/** Allocates a new company */
Company companyCreate(char* email, TechnionFaculty faculty){
    Company company = malloc(sizeof(*company));
    if (!company) {
        return NULL;
    }
    company->email=malloc((sizeof(char)*strlen(email))+1);
    if (!company->email) {
        return NULL;
    }
    strcpy(company->email,email);
    company->Faculty=faculty;
    company->rooms=malloc(sizeof(Set));
    if(!company->rooms){
        return NULL;
    }
    return company;
}

/** Frees an existing company object */
void companyDestroy(Company company){
    free(company->rooms);
    free(company->email);
    free(company);
}

/** Allocates a new company which is a copy of the argument */
Company companyCopy(Company company){
    if (!company) {
        return NULL;
    }
    return companyCreate(company->email,company->Faculty);
}
/** Returns true if both email company are identical */
bool companyEquals(Company company1, Company company2) {
    assert(company1 && company2);
    return strcmp(company1->email,company2->email)==0;
}
char* getEmailCompany(Company company){
    if(!company){
        return NULL;
    }
    return company->email;
}

TechnionFaculty getFacultyOfCompuny(Company company){
    if(!company){
        return NULL;
    }
    return company->Faculty;
}