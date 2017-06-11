//
//  EscapeTechnion.c
//  hw3
//
//  Created by sagi bouzaglo on 28/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//
#include "company.h"
#include "room.h"
#include "order.h"
#include "escaper.h"
#include "EscapeTechnion.h"

#define CHECK_NULL(ptr) if (ptr==NULL){\
                            return MTM_NULL_PARAMETER;\
                            };

struct escapetechnion {
    int day;
    Set company;
    Set escaper;
    List orders;
    int* profit;
};

MtmErrorCode create_EscapeTechnion(EscapeTechnion *EscapeTechnion){
   CHECK_NULL(EscapeTechnion);
   *EscapeTechnion = malloc(sizeof(EscapeTechnion));
   if(!*EscapeTechnion){
      return MTM_OUT_OF_MEMORY;
   }
   (*EscapeTechnion)->company = setCreate(companyCopy,companyDestroy,companyCompare);
   (*EscapeTechnion)->escaper = setCreate(escaperCopy,escaperDestroy,escaperEquals);



   return MTM_SUCCESS;
}

MtmErrorCode destroy_EscapeTechnion(){

   return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_add_company(){

   return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_remove_company(){

   return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_add_room(){

   return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_remove_room(){

   return MTM_SUCCESS;
}


MtmErrorCode EscapeTechnion_add_escaper(){

   return MTM_SUCCESS;
}


MtmErrorCode EscapeTechnion_remove_escaper(){

   return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_add_order(){

   return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_day(){

   return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_best_faculty(){

   return MTM_SUCCESS;
}




