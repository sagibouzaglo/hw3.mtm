//
//  parser.h
//  hw3
//
//  Created by sagi bouzaglo on 08/06/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef parser_h
#define parser_h


#include <stdio.h>
#include "mtm_ex3.h"
#include "list.h"
#include "set.h"
#include "EscapeTechnion.h"
#include <string.h>
#include <stdio.h>


MtmErrorCode get_command(FILE* input,FILE* output,EscapeTechnion *EscapeTechnion);
MtmErrorCode company_command(FILE* input,FILE* output,EscapeTechnion *EscapeTechnion);
MtmErrorCode room_command(FILE* input,FILE* output,EscapeTechnion *EscapeTechnion);
MtmErrorCode escaper_command(FILE* input,FILE* output,EscapeTechnion *EscapeTechnion);
MtmErrorCode report_command(FILE* input,FILE* output,EscapeTechnion *EscapeTechnion);
MtmErrorCode close_channels(FILE* input, FILE* output);
#endif /* parser_h */
