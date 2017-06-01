//
//  company.c
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//


#include "company.h"
#include "order.h"
#include "room.h"
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
    setCreate(roomCopy,roomDestroy,roomCompare); //<---void* in room.c
    if(!company->rooms){
        return  NULL;
    }
    return company;
}

/** Frees an existing company object */
void companyDestroy(void* company){
    setDestroy(((Company)company)->rooms);
    free(((Company)company)->email);
    free(company);
}

/** Allocates a new company which is a copy of the argument */
void* companyCopy(void* company){
    if (!company) {
        return NULL;
    }
    return companyCreate(((Company)company)->email,((Company)company)->Faculty);
}
/** Returns true if both email company are identical */
int companyCompare(void* company1, void* company2) {
    assert(company1 && company2);
    return strcmp(((Company)company1)->email,((Company)company2)->email)==0;
}
char* getEmailCompany(Company company){
    if(!company){
        return NULL;
    }
    char* emailReturn = malloc(sizeof(strlen(company->email)+1));
    if(!emailReturn){
        return NULL;
    }
    strcpy(company->email,emailReturn);
    return emailReturn;
}

TechnionFaculty getFacultyOfCompuny(Company company){
    if(!company){
        return NULL;
    }
    return company->Faculty;
}