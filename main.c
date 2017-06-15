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

#define CHECK_NULL(ptr) if (ptr==NULL){\
                            return MTM_NULL_PARAMETER;\
                        };

#define MAX 256
int main(int argc, char* argv[]) {
    // setting input and output channels
    EscapeTechnion EscapeTechnion = NULL;
    create_EscapeTechnion(&EscapeTechnion);
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
                if(!input) {
                    mtmPrintErrorMessage(stderr,MTM_CANNOT_OPEN_FILE);
                    return 0;
                }
                break;
            }else if (strcmp(argv[1],"-o")==0){
                output = fopen(argv[2],"w");
                if(!output) {
                    mtmPrintErrorMessage(stderr,MTM_CANNOT_OPEN_FILE);
                    return 0;
                }
                break;
            } else {
                mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
                return 0;
            }
        case 5:
            if (strcmp(argv[1],"-i")==0 && strcmp(argv[3],"-o")==0){
                input = fopen(argv[2],"r");
                if(!input) {
                    mtmPrintErrorMessage(stderr,MTM_CANNOT_OPEN_FILE);
                    return 0;
                }
                output = fopen(argv[4],"w");
                if(!output) {
                    fclose(input);
                    mtmPrintErrorMessage(stderr,MTM_CANNOT_OPEN_FILE);
                    return 0;
                }
                break;
            } else if (strcmp(argv[1],"-o")==0 && strcmp(argv[3],"-i")==0){
                input = fopen(argv[4],"r");
                if(!input) {
                    mtmPrintErrorMessage(stderr,MTM_CANNOT_OPEN_FILE);
                    return 0;
                }
                output = fopen(argv[2],"w");
                if(!output) {
                    fclose(input);
                    mtmPrintErrorMessage(stderr,MTM_CANNOT_OPEN_FILE);
                    return 0;
                }
                break;
            } else {
                mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
                return 0;
            }
        default:
            mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
            return 0;
    }
    get_command(input, output, &EscapeTechnion);

    close_channels(input, output);
    return 0;
}
