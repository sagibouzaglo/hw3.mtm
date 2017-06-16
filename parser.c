//
//  parser.c
//  hw3
//
//  Created by sagi bouzaglo on 08/06/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "mtm_ex3.h"
#include "order.h"
#include "EscapeTechnion.h"


#define CHECK_FILE(ptr) if (ptr==NULL) return MTM_CANNOT_OPEN_FILE;
#define MAX 256

/**
 * check the type of "company" command and call the relevant function.
 */
MtmErrorCode company_command(FILE* input,FILE* output,
                                                EscapeTechnion EscapeTechnion){
    char buffer[MAX],email[MAX];
    fscanf(input, " %s", buffer);
    assert(buffer);
    if(strcmp(buffer,"company")==0){
        fscanf(input, " %s", buffer);
        assert(buffer);
        if (strcmp(buffer,"add")==0){
            TechnionFaculty faculty;
            int tmp=0;
            fscanf(input, " %s %d", email,&tmp);
            assert(*email && tmp);
            faculty=(TechnionFaculty)tmp;
            EscapeTechnion_add_company(email,EscapeTechnion,faculty);
        }else if (strcmp(buffer,"remove")==0){
            fscanf(input, " %s", email);
            assert(*email);
            EscapeTechnion_remove_company(email,EscapeTechnion);
        }
    }
    return MTM_SUCCESS;
}

/**
 * check the type of "room" command and call the relevant function.
 */
MtmErrorCode room_command(FILE* input,FILE* output,
                                                EscapeTechnion EscapeTechnion){
    char buffer[MAX];
    int id=0;
    fscanf(input, " %s", buffer);
    assert(buffer);
    if (strcmp(buffer,"room")==0){
        fscanf(input, " %s", buffer);
        if (strcmp(buffer,"add")==0){
            char email[256],working_hrs[5];
            int price=0,num_ppl=0,difficulty=0;
            fscanf(input, " %s %d %d %d %s %d", email,&id,&price,&num_ppl,
                                                       working_hrs,&difficulty);
            assert(*email && id && price && num_ppl &&
                                        *working_hrs && difficulty);
            EscapeTechnion_add_room(email,id,price,num_ppl,working_hrs,difficulty,EscapeTechnion);
        }else if (strcmp(buffer,"remove")==0){
            TechnionFaculty faculty;
            int tmp=0;
            fscanf(input, " %d %d", &tmp,&id);
            assert(tmp && id);
            faculty=(TechnionFaculty)tmp;
            EscapeTechnion_remove_room(faculty,id,EscapeTechnion);
        }
    }
    return MTM_SUCCESS;
}

/**
 *   check the type of "escaper" command and call the relevant function.
 */
MtmErrorCode escaper_command(FILE* input,FILE* output,
                                                EscapeTechnion EscapeTechnion){
    char buffer[256],email[256],time[5];
    int tmp=0,num_ppl=0;
    TechnionFaculty faculty;
    fscanf(input, " %s", buffer);
    assert(buffer);
    //if (strcmp(buffer,"escaper")==0){
       // fscanf(input, " %s", buffer);
       // assert(buffer);
        if (strcmp(buffer,"add")==0){
            int skill_level=1;
            fscanf(input, " %s %d %d", email,&tmp, &skill_level);
            assert(*email && tmp && skill_level);
            faculty=(TechnionFaculty)tmp;
            EscapeTechnion_add_escaper(email,faculty,skill_level,EscapeTechnion);

        }else if (strcmp(buffer,"remove")==0){
            fscanf(input, " %s", email);
            assert(*email);
            EscapeTechnion_remove_escaper(email,EscapeTechnion);
        }else if (strcmp(buffer,"order")==0){
            int id=0;

            fscanf(input, " %s %d %d %s %d", email,&tmp, &id, time, &num_ppl);
            assert(*email && id && tmp && time && num_ppl);
            faculty=(TechnionFaculty)tmp;
            EscapeTechnion_add_order(email,faculty,id,time,num_ppl,EscapeTechnion);
        }else if (strcmp(buffer,"best")==0){
            fscanf(input, " %s %d", email, &num_ppl);
             assert(*email && num_ppl);
            technion_report_day(output,EscapeTechnion);
        }

    return MTM_SUCCESS;
}


/** 
 *   check the type of "report" command and call the relevant function.
 */
MtmErrorCode report_command(FILE* input,FILE* output,
                                                EscapeTechnion EscapeTechnion){
    char buffer[256];
    fscanf(input, " %s", buffer);
    assert(buffer);
    if (strcmp(buffer,"report")==0){
        fscanf(input, " %s", buffer);
        assert(buffer);
        if (strcmp(buffer,"day")==0){
            technion_report_day(output, EscapeTechnion);
        }else if (strcmp(buffer,"best")==0){
            MtmErrorCode buff= technion_report_best(output,EscapeTechnion);
            if(buff!=MTM_SUCCESS){
                return buff;
            }
        }
    }
    return MTM_SUCCESS;
}
/** 
 *   get the type of command and call for the relecant function
 */
void get_command(FILE* input,FILE* output,
                                                EscapeTechnion EscapeTechnion){
    MtmErrorCode error_code=MTM_SUCCESS;
    char buffer[256];
    while (fscanf(input," %s",buffer) != EOF) {
        assert(buffer);
        if (buffer[0] == '#') {
            fscanf(input, "*[^\n]\n");
        } else if (strcmp(buffer, "company") == 0) {
            printf("company_command\n");
            error_code = company_command(input, output, EscapeTechnion);
        } else if (strcmp(buffer, "room") == 0) {
            printf("room_command\n");
            error_code =  room_command(input, output, EscapeTechnion);
        } else if (strcmp(buffer, "escaper") == 0) {
            printf("escaper_command\n");
            error_code = escaper_command(input, output, EscapeTechnion);
        } else if (strcmp(buffer, "report") == 0) {
            printf("report_command\n");
            error_code = report_command(input, output, EscapeTechnion);
        }
        if (error_code != MTM_SUCCESS) {
            mtmPrintErrorMessage(stderr, error_code);
        }
    }
}

/**
 *  if input/output channels are files closes them
 */
MtmErrorCode close_channels(FILE* input, FILE* output){
    if ((input != stdin)&&(input!=NULL)){
        fclose(input);
    }
    if ((output != stdout)&&(output!=NULL)){
            fclose(output);
    }
    return MTM_SUCCESS;
}
