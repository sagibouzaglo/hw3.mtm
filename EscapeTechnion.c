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
#define CHECK_FILE(ptr) if (ptr==NULL){\
                            return MTM_CANNOT_OPEN_FILE;\
                            };
MtmErrorCode set_input_output(FILE* input, FILE* output, Check check);
MtmErrorCode get_input_output(FILE* input, FILE* output);
MtmErrorCode get_command(FILE* input,FILE* output);
MtmErrorCode company_command(FILE* input,FILE* output);
MtmErrorCode room_command(FILE* input,FILE* output);
MtmErrorCode escaper_command(FILE* input,FILE* output);
MtmErrorCode report_command(FILE* input,FILE* output);


int main(int argc, char **argv){
    // setting input and output channels
    FILE *input = stdin;
    CHECK_NULL(input);
    FILE *output = stdout;
    CHECK_NULL(output);
    FILE *error_channel = stderr;
    CHECK_NULL(error_channel);
    MtmErrorCode check = get_input_output(input,output);
    while (check == MTM_SUCCESS){
        check = get_command(input,output);
        if (check != MTM_SUCCESS){
            mtmPrintErrorMessage(error_channel,check);
            check = MTM_SUCCESS;
        }
    }
    return check;
}


MtmErrorCode get_input_output(FILE* input, FILE* output){
    char buffer[256], buffer2[2];
    Check check=OK;
    MtmErrorCode ret_value;
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
            ret_value = set_input_output(input,output,check);
            if (ret_value != MTM_SUCCESS){
                return ret_value;
            };
        }
    }
    return MTM_SUCCESS;
}

// read the input/output channel and set it
MtmErrorCode set_input_output(FILE* input, FILE* output, Check check){
    char buffer[256];
    switch (check){
        case INPUT:
            fscanf(input," %s", buffer);
            input = fopen(buffer,"r");
            CHECK_FILE(input);
            break;
        case OUTPUT:
            fscanf(input," %s", buffer);
            output = fopen(buffer,"w");
            CHECK_FILE(output);
            break;
        // should not get here
        default:
            break;
    }
    return MTM_SUCCESS;
}

// get the type of command and call for the relecant function
MtmErrorCode get_command(FILE* input,FILE* output){
    char buffer[256];
    fscanf(input, " %s", buffer);
    if (strcmp(buffer,"company")==0){
        company_command(input,output);
    }else if (strcmp(buffer,"room")==0){
        room_command(input,output);
    }else if (strcmp(buffer,"escaper")==0){
        escaper_command(input,output);
    }else if (strcmp(buffer,"report")==0){
        report_command(input,output);
    }
    return MTM_SUCCESS;
}
