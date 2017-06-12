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
static bool IfEmailValid(char* email);
struct escaper {
    char* email;
    TechnionFaculty Faculty;
    int skill_level;
};


/** Allocates a new escaper */
Escaper escaperCreate(char* email, TechnionFaculty faculty , int skill_level,EscaperReturn* Result){
    if(!IfEmailValid(email)){
        *Result= Esc_INVALID_PARAMETER;
        return NULL;
    }
    Escaper escaper = malloc(sizeof(*escaper));
    if (!escaper) {
        *Result= Esc_OUT_OF_MEMORY;
        return NULL;
    }
    escaper->email=malloc((sizeof(char)*strlen(email))+1);
    if (!escaper->email) {
        *Result= Esc_OUT_OF_MEMORY;
        return NULL;
    }
    strcpy(escaper->email,email);
    escaper->Faculty=faculty;
    escaper->skill_level=skill_level;
    return escaper;
}

/** Frees an existing escaper object */
void escaperDestroy(void* escaper){
    free(((Escaper)escaper)->email);
    free(escaper);
}

/** Allocates a new escaper which is a copy of the argument */
void* escaperCopy(void* escaper){
    if (!escaper) {
        return NULL;
    }
    EscaperReturn Result;
    return escaperCreate(((Escaper)escaper)->email,((Escaper)escaper)->Faculty,((Escaper)escaper)->skill_level, &Result);
}

/** Returns true if both email escaper are identical */
int escaperEquals(void* escaper1, void* escaper2) {
    if( !escaper1 || !escaper2){
        return NULL;
    }
    EscaperReturn Result;
    return strcmp(((Escaper)escaper1)->email,((Escaper)escaper2)->email);
}

char* getEmailEscaper(Escaper escaper,EscaperReturn* Result){
    if(!escaper){
        *Result= Esc_NULL_PARAMETER;
        return NULL;
    }
    char* emailReturn = malloc(sizeof(strlen(escaper->email)+1));
    if(!emailReturn){
        *Result= Esc_OUT_OF_MEMORY;
        return NULL;
    }
    strcpy(escaper->email,emailReturn);
    return emailReturn;
}
int getSkillLevel(Escaper escaper){
    if(!escaper){
        return NULL;
    }
    return escaper->skill_level;
}

TechnionFaculty getFacultyEscaper(Escaper escaper){
    if(!escaper){
        return NULL;
    }
    return escaper->Faculty;
}
static bool IfEmailValid(char* email) {
    if (!email) {
        return NULL;
    }
    int counter = 0;
    for (int i = 0; i < strlen(email); ++i) {
        if (*(email + i) == '@') {
            ++counter;
            if (counter > 1) {
                return false;
            }
        }
    }
    if (counter == 1) {
        return true;
    }
    return false;
}

