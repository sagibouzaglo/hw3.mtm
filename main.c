//
//  main.c
//  hw3
//
//  Created by sagi bouzaglo on 21/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include <stdio.h>
#include "EscapeTechnion.h"
#include "mtm_ex3.h"
#include "parser.h"

#define CHECK_NULL(ptr) if (!ptr){\
                            return MTM_NULL_PARAMETER;\
                        };
#define CHECK_FILE(ptr,dest,err)\
                                if (!ptr){\
                                    mtmPrintErrorMessage(dest,err);\
                                    return  0;\
                                };
#define CHECK_FILE_AND_CLOSE(ptr,close,dest,err)\
                                            if (!ptr){\
                                                mtmPrintErrorMessage(dest,err);\
                                                fclose(close);\
                                                return  0;\
                                            };

#define MAX 256
int main(int argc, char* argv[]) {
    // setting input and output channels
    EscapeTechnion EscapeTechnion1;

    if(create_EscapeTechnion(&EscapeTechnion1)!= MTM_SUCCESS) return 0;

    FILE *input = stdin;
    CHECK_NULL(input);
    FILE *output = stdout;
    CHECK_NULL(output);
    switch(argc){
        case 1:
            break;
        case 3:
            if (strcmp(argv[1],"-i")==0){
                input = fopen(argv[2],"r");
                CHECK_FILE(input, stderr, MTM_CANNOT_OPEN_FILE);
                break;
            }else if (strcmp(argv[1],"-o")==0){
                output = fopen(argv[2],"w");
                CHECK_FILE(output, stderr, MTM_CANNOT_OPEN_FILE);
                break;
            } else {
                mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
                return 0;
            }
        case 5:
            if (strcmp(argv[1],"-i")==0 && strcmp(argv[3],"-o")==0){
                input = fopen(argv[2],"r");
                CHECK_FILE(input, stderr, MTM_CANNOT_OPEN_FILE);
                output = fopen(argv[4],"w");
                CHECK_FILE_AND_CLOSE(output,input,stderr,MTM_CANNOT_OPEN_FILE);
                break;
            } else if (strcmp(argv[1],"-o")==0 && strcmp(argv[3],"-i")==0){
                input = fopen(argv[4],"r");
                CHECK_FILE(input, stderr, MTM_CANNOT_OPEN_FILE);
                output = fopen(argv[2],"w");
                CHECK_FILE_AND_CLOSE(output,input,stderr,MTM_CANNOT_OPEN_FILE);
                break;
            } else {
                mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
                return 0;
            }
        default:
            mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
            return 0;
    }
    get_command(input, output, EscapeTechnion1);
    close_channels(input, output);

    return 0;
}
