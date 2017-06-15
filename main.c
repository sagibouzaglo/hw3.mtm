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
#define CHECK_FILE(ptr) if (ptr==NULL){\
                            return MTM_CANNOT_OPEN_FILE;\
                        };
#define MAX 256
int main(int argc, const char * argv[]) {
    // setting input and output channels
    EscapeTechnion *EscapeTechnion = NULL;
    create_EscapeTechnion(EscapeTechnion);
    FILE *input = stdin;
    CHECK_NULL(input);
    FILE *output = stdout;
    CHECK_NULL(output);
    char buffer[MAX];
    MtmErrorCode error_code;
    
    if (argc <=5){
        switch(argc){
            case 1:
                break;
            case 2:
            case 4:
                mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
                break;
            case 3:
            case 5:
                if (strcmp(argv[2],"-i")==0){
                    input = fopen(argv[3],"r");
                    CHECK_FILE(input);
                }else if (strcmp(argv[2],"-o")==0){
                    output = fopen(argv[3],"w");
                    CHECK_FILE(output);
                }
                
                break;
        }
    }
       while (fscanf(input," %s",buffer) != EOF){
        error_code = get_command(input,output,EscapeTechnion);
        if (error_code != MTM_SUCCESS){
            mtmPrintErrorMessage(stderr, error_code);
        }
    }
    close_channels(input,output);
    return 0;
}
