//
//  main.c
//  hw3
//
//  Created by sagi bouzaglo on 21/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include <stdio.h>
#include "mtm_ex3.h"
#include "parser.h"
#define CHECK_NULL(ptr) if (ptr==NULL){\
                            return MTM_NULL_PARAMETER;\
                        };
#define CHECK_FILE(ptr) if (ptr==NULL){\
                            return MTM_CANNOT_OPEN_FILE;\
                        };

int main(int argc, const char * argv[]) {
          // setting input and output channels
    
        FILE *input = stdin;
        CHECK_NULL(input);
        FILE *output = stdout;
        CHECK_NULL(output);
        FILE *error_channel = stderr;
        CHECK_NULL(error_channel);
        char buffer[256], buffer2[2];
        Check check=OK;
        MtmErrorCode error_code;
        while (fscanf(input," %s",buffer) != EOF){
            // check legal statment
            if (strcmp(buffer,"mtm_escape")){
                    fscanf(input, " %s", buffer2);
                    if (strcmp("-i",buffer2)==0){
                        check = INPUT;
                    }else if (strcmp("-o",buffer2)==0){
                        check = OUTPUT;
                    }else{
                        check = FAILED;
                    }
                    error_code = set_input_output(input,output,check);
                    if (error_code != MTM_SUCCESS){
                        return error_code;
                }
            }
        }
        error_code = get_command(input,output);
        if (error_code != MTM_SUCCESS){
            mtmPrintErrorMessage(error_channel,error_code);
            error_code = MTM_SUCCESS;
        }
        return check;
}
