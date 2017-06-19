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
 * get the company commend from the input and call the relevany function
 *
 * @param input - input channel.
 * @param output - output channel.
 * @param EscapeTechnion1 - a pointer to the system adt.
 *
 * @return result
 * MTM_NULL_PARAMETER - one of the sent pointers is NULL.
 * MTM_OUT_OF_MEMORY - allocation failed.
 * MTM_EMAIL_ALREADY_EXISTS - company email already exist.
 * MTM_COMPANY_EMAIL_DOES_NOT_EXIST - the company mail doesn't exist.
 * MTM_RESERVATION_EXISTS - there is a reservation for the room.
 * MTM_SUCCESS - company commend finished successfully.
 */
MtmErrorCode company_command(FILE* input,FILE* output,
                                                EscapeTechnion EscapeTechnion1){
    char buffer[MAX],email[MAX];
    fscanf(input, " %s", buffer);
    assert(buffer);
        if (strcmp(buffer,"add")==0){
            TechnionFaculty faculty;
            int tmp=0;
            fscanf(input, " %s %d", email,&tmp);
            assert(*email && tmp);
            faculty=(TechnionFaculty)tmp;
            EscapeTechnion_add_company(email,EscapeTechnion1,faculty);
        }else if (strcmp(buffer,"remove")==0){
            fscanf(input, " %s", email);
            assert(*email);
            EscapeTechnion_remove_company(email,EscapeTechnion1);
        }

    return MTM_SUCCESS;
}

/**
 * get the room commend from the input and call the relevany function
 *
 * @param input - input channel.
 * @param output - output channel.
 * @param EscapeTechnion1 - a pointer to the system adt.
 *
 * @return result
 * MTM_NULL_PARAMETER - one of the sent pointers is NULL.
 * MTM_COMPANY_EMAIL_DOES_NOT_EXIST - the  mail sent is NULL.
 * MTM_ID_ALREADY_EXIST - the sent id already exist.
 * MTM_ID_DOES_NOT_EXIST - the sent room id doesn't exist.
 * MTM_RESERVATION_EXISTS - there is a reservation for the room we want to remove.
 * MTM_SUCCESS -   room commend finished successfully.
 */
MtmErrorCode room_command(FILE* input,FILE* output,
                                                EscapeTechnion EscapeTechnion1){
    char buffer[MAX];
    int id=0;
    fscanf(input, " %s", buffer);
    assert(buffer);

        if (strcmp(buffer,"add")==0){
            char email[256],working_hrs[5];
            int price=0,num_ppl=0,difficulty=0;
            fscanf(input, " %s %d %d %d %s %d", email,&id,&price,&num_ppl,
                                                       working_hrs,&difficulty);
        assert(*email && id && price && num_ppl &&
                                        *working_hrs && difficulty);
            EscapeTechnion_add_room(email,id,price,num_ppl,working_hrs,difficulty,EscapeTechnion1);
        }else if (strcmp(buffer,"remove")==0){
            TechnionFaculty faculty;
            int tmp=0;
            fscanf(input, " %d %d", &tmp,&id);
            assert(tmp && id);
            faculty=(TechnionFaculty)tmp;
            EscapeTechnion_remove_room(faculty,id,EscapeTechnion1);
        }

    return MTM_SUCCESS;
}

/**
 * get the escaper commend from the input and call the relevany function
 *
 * @param input - input channel.
 * @param output - output channel.
 * @param EscapeTechnion1 - a pointer to the system adt.
 *
 * @return result
 * MTM_NULL_PARAMETER - one of the sent pointers is NULL.
 * MTM_CLIENT_EMAIL_DOES_NOT_EXIST - the mail sent is already exist for other escaper.
 * MTM_INVALID_PARAMETER - one of the sent pointers is NULL.
 * MTM_ID_DOES_NOT_EXIST - the id sent doesn't match any room.
 * MTM_OUT_OF_MEMORY - allocation failed.
 * MTM_NO_ROOMS_AVAILABLE - there are no rooms available.
 * MTM_CLIENT_IN_ROOM - escaper have another order for the same day and hour.
 * MTM_ROOM_NOT_AVAILABLE - the asked room is unavailable.
 * MTM_SUCCESS - escaper commend finished successfully.
 */
MtmErrorCode escaper_command(FILE* input,FILE* output,
                                                EscapeTechnion EscapeTechnion1){
    char buffer[256],email[256],time[5];
    int tmp=0,num_ppl=0;
    TechnionFaculty faculty;
    fscanf(input, " %s", buffer);
    assert(buffer);

        if (strcmp(buffer,"add")==0){

            int skill_level=1;
            fscanf(input, " %s %d %d", email,&tmp, &skill_level);
            assert(*email && tmp && skill_level);
            faculty=(TechnionFaculty)tmp;
            EscapeTechnion_add_escaper(email,faculty,skill_level,EscapeTechnion1);
        }else if (strcmp(buffer,"remove")==0){
            fscanf(input, " %s", email);
            assert(*email);
            EscapeTechnion_remove_escaper(email,EscapeTechnion1);
        }else if (strcmp(buffer,"order")==0){
            int id=0;

            fscanf(input, " %s %d %d %s %d", email,&tmp, &id, time, &num_ppl);
            assert(*email && id && tmp && time && num_ppl);
            faculty=(TechnionFaculty)tmp;
            MtmErrorCode err = EscapeTechnion_add_escaper_order(email,faculty,id,time,num_ppl,EscapeTechnion1);
            if(err != MTM_SUCCESS) return err;
        }else if (strcmp(buffer,"recommend")==0){
            fscanf(input, " %s %d", email, &num_ppl);
            assert(*email && num_ppl);
            MtmErrorCode err = EscapeTechnion_add_escaper_recommend(email,num_ppl,EscapeTechnion1);
            if(err != MTM_SUCCESS)return err;
        }
    return MTM_SUCCESS;
}

/**
 * get the report commend from the input and call the relevany function
 *
 * @param input - input channel.
 * @param output - output channel.
 * @param EscapeTechnion1 - a pointer to the system adt.
 *
 * @return result
 * MTM_INVALID_PARAMETER - one of the sent pointers is NULL.
 * MTM_OUT_OF_MEMORY - allocation failed.
 * MTM_NO_ROOMS_AVAILABLE - no rooms available.
 * MTM_SUCCESS - report commend finished successfully.
 */
MtmErrorCode report_command(FILE* input,FILE* output,
                                                EscapeTechnion EscapeTechnion1){

    char buffer[256];
    fscanf(input, " %s", buffer);
    assert(buffer);

        if (strcmp(buffer,"day")==0){
            technion_report_day(output, EscapeTechnion1);
        }else if (strcmp(buffer,"best")==0){
            MtmErrorCode buff= technion_report_best(output,EscapeTechnion1);
            if(buff!=MTM_SUCCESS){
                return buff;
            }
        }

    return MTM_SUCCESS;
}

/** 
 *  get the type of command and call the relevant function
 *
 * @param input - input channel.
 * @param output - output channel.
 * @param EscapeTechnion1 - a pointer to the system adt.
 *
 */
void get_command(FILE* input,FILE* output,EscapeTechnion EscapeTechnion1){
    MtmErrorCode error_code=MTM_SUCCESS;
    char buffer[256];
    while (fscanf(input," %s",buffer) != EOF) {
        assert(buffer);
        if (buffer[0] == '#') {
            fscanf(input, "%*[^\n]\n");
        } else if (strcmp(buffer, "company") == 0) {
            error_code = company_command(input, output, EscapeTechnion1);
        } else if (strcmp(buffer, "room") == 0) {
            error_code =  room_command(input, output, EscapeTechnion1);
        } else if (strcmp(buffer, "escaper") == 0) {
            error_code = escaper_command(input, output, EscapeTechnion1);
        } else if (strcmp(buffer, "report") == 0) {
            error_code = report_command(input, output, EscapeTechnion1);
        }
        if (error_code != MTM_SUCCESS) {
            mtmPrintErrorMessage(stderr, error_code);
        }
    }
}

/**
 *  close the input and output channels
 *
 * @param input - input channel.
 * @param output - output channel.
 *
 * @return result
 * MTM_SUCCESS - channels closed successfully.
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
