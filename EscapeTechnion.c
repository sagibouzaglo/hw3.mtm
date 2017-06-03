//
//  EscapeTechnion.c
//  hw3
//
//  Created by sagi bouzaglo on 28/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "EscapeTechnion.h"
typedef enum check {INPUT=1,
                    OUTPUT,
                    FAILED,
                    OK}Check;
#define CHECK_NULL(ptr) if (ptr==NULL){\
                            return MTM_NULL_PARAMETER;\
                            };
MtmErrorCode set_input_output(FILE* input, FILE* output, Check check);

int main(int argc, char **argv){
    char* buffer, buffer2[2];
    Check check=OK;
    // setting input and output channels
    FILE *input = stdin;
    CHECK_NULL(input);
    FILE *output = stdout;
    CHECK_NULL(output);
    fscanf(input," %s",buffer);
    // check legal statment
    if (strcmp(buffer,"mtm_escape")){
        while(check != FAILED){
            fscanf(input, " %s", buffer2);
            if (strcmp("-i",buffer2)==0){
                check = INPUT;
            }else if (strcmp("-o",buffer2)==0){
                check = OUTPUT;
            }else{
                check = FAILED;
            }
            if (set_input_output(input,output,check)!= MTM_SUCCESS){
                return MTM_CANNOT_OPEN_FILE;
            }; // need to write function
        }
        
    }
    return MTM_SUCCESS;
}


MtmErrorCode set_input_output(FILE* input, FILE* output, Check check){
    
    return MTM_SUCCESS;
}
