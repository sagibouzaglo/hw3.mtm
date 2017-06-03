//
//  EscapeTechnion.c
//  hw3
//
//  Created by sagi bouzaglo on 28/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "EscapeTechnion.h"
enum check {INPUT=1,
            OUTPUT,
            OK};
#define CHECK_NULL(ptr) if (ptr==NULL){\
                            return MTM_NULL_PARAMETER;\
                            };

int main(int argc, char **argv){
    char* buffer, buffer2[2];
    int check=OK;
    // setting input and output channels
    FILE *input = stdin;
    CHECK_NULL(input);
    FILE *output = stdout;
    CHECK_NULL(output);
    fscanf(input," %s",buffer);
    // check legal statment
    if (strcmp(buffer,"mtm_escape")){
        while(check != NULL){
            fscanf(input, " %s", buffer2);
            if (strcmp("-i",buffer2)==0){
                check = INPUT;
            }else if (strcmp("-o",buffer2)==0){
                check = OUTPUT;
            }else{
                check == NULL;
            }
            if (set_input_output(input,output,check)!= MTM_SUCCESS){
                return MTM_CANNOT_OPEN_FILE;
            }; // need to write function
        }
        
    }

    return MTM_SUCCESS;
}
