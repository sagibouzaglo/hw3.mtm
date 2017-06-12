//
//  parser.c
//  hw3
//
//  Created by sagi bouzaglo on 08/06/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "parser.h"

#define CHECK_FILE(ptr) if (ptr==NULL){\
return MTM_CANNOT_OPEN_FILE;\
};

MtmErrorCode set_input_output(FILE* input, FILE* output, Check check);
MtmErrorCode get_command(FILE* input,FILE* output);
MtmErrorCode company_command(FILE* input,FILE* output);
MtmErrorCode room_command(FILE* input,FILE* output);
MtmErrorCode escaper_command(FILE* input,FILE* output);
MtmErrorCode report_command(FILE* input,FILE* output);

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
    if (buffer[0]=='#'){
        fscanf(input, "*[^\n]\n");
    }else if(strcmp(buffer,"company")==0){
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

MtmErrorCode company_command(FILE* input,FILE* output){
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
            technion_company_add(email,faculty);
        }else if (strcmp(buffer,"remove")==0){
            char email[256];
            fscanf(input, " %s", email);
            technion_company_remove(email);
        }
    }
    return MTM_SUCCESS;
}

MtmErrorCode room_command(FILE* input,FILE* output){
    char buffer[256];
    int id=0;
    fscanf(input, " %s", buffer);
    if (strcmp(buffer,"room")==0){
        fscanf(input, " %s", buffer);
        if (strcmp(buffer,"add")==0){
            char email[256],working_hrs[5];
            int price=0,num_ppl=0,difficulty=0;
            fscanf(input, " %s %d %d %d %s %d", email,&id,&price,&num_ppl,working_hrs,&difficulty);
            technion_room_add(email,id,price,num_ppl,working_hrs,difficulty);
        }else if (strcmp(buffer,"remove")==0){
            TechnionFaculty faculty;
            int tmp=0;
            fscanf(input, " %d %d", &tmp,&id);
            faculty=(TechnionFaculty)tmp;
            technion_room_remove(faculty,id);
        }
    }
    return MTM_SUCCESS;
}

MtmErrorCode escaper_command(FILE* input,FILE* output){
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
            technion_escaper_add(email,faculty,skill_level);
        }else if (strcmp(buffer,"remove")==0){
            fscanf(input, " %s", email);
            technion_escaper_remove(email);
        }else if (strcmp(buffer,"order")==0){
            int id=0,time=0;
            fscanf(input, " %s %d %d %d %d", email,&tmp, &id, &time, &num_ppl);
            faculty=(TechnionFaculty)tmp;
            technion_escaper_order(email,faculty,id,time,num_ppl);
        }else if (strcmp(buffer,"order")==0){
            fscanf(input, " %s %d", email, &num_ppl);
            technion_escaper_order(email,num_ppl);
        }
    }
    return MTM_SUCCESS;
}

MtmErrorCode report_command(FILE* input,FILE* output){
    char buffer[256];
    fscanf(input, " %s", buffer);
    if (strcmp(buffer,"report")==0){
        fscanf(input, " %s", buffer);
        if (strcmp(buffer,"day")==0){
            technion_report_day();
        }else if (strcmp(buffer,"best")==0){
            technion_report_best();
        }
    }
    return MTM_SUCCESS;
}
