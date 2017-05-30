//
//  escaper.c
//  hw3
//
//  Created by sagi bouzaglo on 28/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//
#include "company.h"
#include "order.h"
#include "escaper.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define CHECK_NULL(ptr) if (!ptr){\
                            return MTM_NULL_PARAMETER;\
                            };

struct escaper {
    char* email;
    TechnionFaculty Faculty;
    int skill_level;
};


/** Allocates a new escaper */
Escaper escaperCreate(char* email, TechnionFaculty faculty , int skill_level){
    Escaper escaper = malloc(sizeof(*escaper));
    if (!escaper) {
        return NULL;
    }
    escaper->email=malloc((sizeof(char)*strlen(email))+1);
    if (!escaper->email) {
        return NULL;
    }
    strcpy(escaper->email,email);
    escaper->Faculty=faculty;
    escaper->skill_level=skill_level;
    return escaper;
}

/** Frees an existing escaper object */
void escaperDestroy(Escaper escaper){
    free(escaper->email);
    free(escaper);
}

/** Allocates a new escaper which is a copy of the argument */
Escaper companyCopy(Escaper escaper){
    if (!escaper) {
        return NULL;
    }
    return escaperCreate(escaper->email,escaper->Faculty,escaper->skill_level);
}
/** Returns true if both email escaper are identical */
bool escaperEquals(Escaper escaper1, Escaper escaper2) {
    assert(escaper1 && escaper2);
    return strcmp(escaper1->email,escaper2->email)==0;
}
#include "escaper.h"
