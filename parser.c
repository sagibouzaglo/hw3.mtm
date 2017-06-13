//
//  parser.c
//  hw3
//
//  Created by sagi bouzaglo on 08/06/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "mtm_ex3.h"
#include "EscapeTechnion.h"


#define CHECK_FILE(ptr) if (ptr==NULL) return MTM_CANNOT_OPEN_FILE;

/**
 * check the type of "company" command and call the relevant function.
 */
MtmErrorCode company_command(FILE* input,FILE* output,EscapeTechnion *EscapeTechnion){
    char buffer[256];
    fscanf(input, " %s", buffer);
    if(strcmp(buffer,"company")==0){
        fscanf(input, " %s", buffer);
        if (strcmp(buffer,"add")==0){
            char email[256];
            TechnionFaculty faculty;
            int tmp=0;
            fscanf(input, " %s %d", email,&tmp);
            faculty=(TechnionFaculty)tmp;
            technion_company_add(email,faculty,EscapeTechnion);
        }else if (strcmp(buffer,"remove")==0){
            char email[256];
            fscanf(input, " %s", email);
            technion_company_remove(email,EscapeTechnion);
        }
    }
    return MTM_SUCCESS;
}

/**
 * check the type of "room" command and call the relevant function.
 */
MtmErrorCode room_command(FILE* input,FILE* output,EscapeTechnion *EscapeTechnion){
    char buffer[256];
    int id=0;
    fscanf(input, " %s", buffer);
    if (strcmp(buffer,"room")==0){
        fscanf(input, " %s", buffer);
        if (strcmp(buffer,"add")==0){
            char email[256],working_hrs[5];
            int price=0,num_ppl=0,difficulty=0;
            fscanf(input, " %s %d %d %d %s %d", email,&id,&price,&num_ppl,working_hrs,&difficulty);
            technion_room_add(email,id,price,num_ppl,working_hrs,difficulty,EscapeTechnion);
        }else if (strcmp(buffer,"remove")==0){
            TechnionFaculty faculty;
            int tmp=0;
            fscanf(input, " %d %d", &tmp,&id);
            faculty=(TechnionFaculty)tmp;
            technion_room_remove(faculty,id,EscapeTechnion);
        }
    }
    return MTM_SUCCESS;
}

/**
 *   check the type of "escaper" command and call the relevant function.
 */
MtmErrorCode escaper_command(FILE* input,FILE* output, EscapeTechnion *EscapeTechnion){
    char buffer[256],email[256];
    int tmp=0,num_ppl=0;
    TechnionFaculty faculty;
    fscanf(input, " %s", buffer);
    if (strcmp(buffer,"escaper")==0){
        fscanf(input, " %s", buffer);
        if (strcmp(buffer,"add")==0){
            int skill_level=1;
            fscanf(input, " %s %d %d", email,&tmp, &skill_level);
            faculty=(TechnionFaculty)tmp;
            technion_escaper_add(email,faculty,skill_level,EscapeTechnion);
        }else if (strcmp(buffer,"remove")==0){
            fscanf(input, " %s", email);
            technion_escaper_remove(email,EscapeTechnion);
        }else if (strcmp(buffer,"order")==0){
            int id=0,time=0;
            fscanf(input, " %s %d %d %d %d", email,&tmp, &id, &time, &num_ppl);
            faculty=(TechnionFaculty)tmp;
            technion_escaper_order(email,faculty,id,time,num_ppl,EscapeTechnion);
        }else if (strcmp(buffer,"order")==0){
            fscanf(input, " %s %d", email, &num_ppl);
            technion_escaper_order(email,num_ppl,EscapeTechnion);
        }
    }
    return MTM_SUCCESS;
}


/** 
 *   check the type of "report" command and call the relevant function.
 */
MtmErrorCode report_command(FILE* input,FILE* output,EscapeTechnion *EscapeTechnion){
    char buffer[256];
    fscanf(input, " %s", buffer);
    if (strcmp(buffer,"report")==0){
        fscanf(input, " %s", buffer);
        if (strcmp(buffer,"day")==0){
            technion_report_day(output, EscapeTechnion);
        }else if (strcmp(buffer,"best")==0){
            technion_report_best(EscapeTechnion);
        }
    }
    return MTM_SUCCESS;
}
/** 
 *   get the type of command and call for the relecant function
 */
MtmErrorCode get_command(FILE* input,FILE* output,EscapeTechnion *EscapeTechnion){
    char buffer[256];
    fscanf(input, " %s", buffer);
    if (buffer[0]=='#'){
        fscanf(input, "*[^\n]\n");
    }else if(strcmp(buffer,"company")==0){
        company_command(input,output,EscapeTechnion);
    }else if (strcmp(buffer,"room")==0){
        room_command(input,output,EscapeTechnion);
    }else if (strcmp(buffer,"escaper")==0){
        escaper_command(input,output,EscapeTechnion);
    }else if (strcmp(buffer,"report")==0){
        report_command(input,output,EscapeTechnion);
    }
    return MTM_SUCCESS;
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
