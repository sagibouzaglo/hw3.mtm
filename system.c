//
//  system.c
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "system.h"

#define CHECK_NULL(ptr) if (ptr==NULL){\
                            return MTM_NULL_PARAMETER;\
                            };
#define CHECK_MEMORY(ptr) if (ptr==NULL){\
                            return MTM_OUT_OF_MEMORY;\
                            };

struct system {
    int day;
    Set company;
    Set escaper;
    List orders;
    int profit[(((int)UNKNOWN)+1)];
};

int create_system(char* init_file, System **sys){
    CHECK_NULL(*sys);
    *sys = malloc(sizeof(System));
    
    return MTM_SUCCESS;
}

int destroy_system(){
    
    return MTM_SUCCESS;
}

int system_add_company(){
    
     return MTM_SUCCESS;
}

int system_remove_company(){
    
    return MTM_SUCCESS;
}

int system_add_room(){
    
    return MTM_SUCCESS;
}

int system_remove_room(){
    
    return MTM_SUCCESS;
}


int system_add_escaper(){
    
    return MTM_SUCCESS;
}


int system_remove_escaper(){
    
    return MTM_SUCCESS;
}

int system_add_order(){
    
    return MTM_SUCCESS;
}

int system_day(){
    
    return MTM_SUCCESS;
}

int system_best_faculty(){
    
    return MTM_SUCCESS;
}


