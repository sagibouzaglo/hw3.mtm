//
//  EscapeTechnion.c
//  hw3
//
//  Created by sagi bouzaglo on 28/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "EscapeTechnion.h"

#define CHECK_NULL(ptr) if (ptr==NULL){\
                            return MTM_NULL_PARAMETER;\
                            };

int main(int argc, char **argv){
    char* buffer;
    // setting input and output channels
    FILE *input = fopen(stdin,"r");
    CHECK_NULL(input);
    FILE *output = fopen(stdout,"w");
    CHECK_NULL(output);
    fscanf(input, "%s",buffer);
    if (strcmp(buffer,"mtm_escape")){
        
    }

    return MTM_SUCCESS;
}
