//
//  parser.h
//  hw3
//
//  Created by sagi bouzaglo on 08/06/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef parser_h
#define parser_h

typedef enum check {INPUT=1,
    OUTPUT,
    FAILED,
    OK}Check;
#include <stdio.h>
#include "mtm_ex3.h"
#include "list.h"
#include "set.h"
#include <string.h>
#include <stdio.h>


MtmErrorCode set_input_output(FILE* input, FILE* output, Check check);


MtmErrorCode get_input_output(FILE* input, FILE* output);


MtmErrorCode get_command(FILE* input,FILE* output);


MtmErrorCode company_command(FILE* input,FILE* output);


MtmErrorCode room_command(FILE* input,FILE* output);


MtmErrorCode escaper_command(FILE* input,FILE* output);


MtmErrorCode report_command(FILE* input,FILE* output);

#endif /* parser_h */
