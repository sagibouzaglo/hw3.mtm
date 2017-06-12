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
#include "company.h"

#define CHECK_NULL(ptr) if (ptr==NULL){\
                            return MTM_NULL_PARAMETER;\
                            };

static MtmErrorCode ifEmailAlreadyExists(char* email,EscapeTechnion *EscapeTechnion);
static Company findCompany (char* email,EscapeTechnion *EscapeTechnion);

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
    (*EscapeTechnion)->orders = listCreate(orderCopy,orderDestroy);
    (*EscapeTechnion)->profit = malloc(sizeof((int)UNKNOWN)+1);
    if (!(*EscapeTechnion)->profit){
         return MTM_OUT_OF_MEMORY;
    }
    (*EscapeTechnion)->day=0;

    return MTM_SUCCESS;
}

MtmErrorCode destroy_EscapeTechnion(EscapeTechnion *EscapeTechnion){
   CHECK_NULL(EscapeTechnion);
   free((*EscapeTechnion)->profit);
   free(*EscapeTechnion);
   return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_add_company(char* email,EscapeTechnion *EscapeTechnion, TechnionFaculty faculty){
    if(!email || !EscapeTechnion){
        return MTM_NULL_PARAMETER;
    }
    MtmErrorCode cheak_email = ifEmailAlreadyExists(email,EscapeTechnion);
    if(cheak_email!=MTM_SUCCESS){
        return cheak_email;
    }
    CompanyReturn Result;
    companyCreate(email,faculty,&Result);
    if(Result==COM_OUT_OF_MEMORY){
        return MTM_OUT_OF_MEMORY;
    }
    if(Result==COM_NULL_PARAMETER){
        return MTM_NULL_PARAMETER;
    }

    return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_remove_company(char* email,EscapeTechnion *EscapeTechnion){
    CHECK_NULL(EscapeTechnion);
    CHECK_NULL(email);
    Company company = findCompany(email,EscapeTechnion);
    if(company==NULL){
        return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
    }

    SET_FOREACH(Room,roomIterator,getCompanyRooms(company)) {
        LIST_FOREACH(Order, iterator_order, (*EscapeTechnion)->orders) {
            if(getRoomIdOrder(iterator_order)==getIdRoom(roomIterator)){
                return MTM_RESERVATION_EXISTS;
            }
        }
    }
    companyDestroy(company);
    return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_add_room(char* email,int id, int price, int num_ppl,
                                     char* working_hour, int difficulty,
                                     EscapeTechnion *EscapeTechnion){
if(!email || !EscapeTechnion || !working_hour){
    return MTM_NULL_PARAMETER;
}
    Company company = findCompany(email,EscapeTechnion);
    if(company==NULL){
        return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
    }
    Room room = roomCreate();
    setAdd(getCompanyRooms(company),room);
    free(room);
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

static MtmErrorCode ifEmailAlreadyExists(char* email,EscapeTechnion *EscapeTechnion){
   CHECK_NULL(email);
   CHECK_NULL(EscapeTechnion);

    SET_FOREACH(Company,iterator_comp,(*EscapeTechnion)->company){
        if(strcmp(email,getEmailCompany((Company)iterator_comp))==0){
            return MTM_EMAIL_ALREADY_EXISTS;
        }
    }
    EscaperReturn Result;
    LIST_FOREACH(Order,iterator_order,(*EscapeTechnion)->orders){
        char* emailCompany = getEmailEscaper(getEscaperOrder((Order)iterator_order),&Result);
        if (Result!=ORD_SUCCESS){
            return (Result==ORD_OUT_OF_MEMORY ? MTM_OUT_OF_MEMORY : MTM_NULL_PARAMETER);
        }
        if(strcmp(email,emailCompany)==0){
            return MTM_EMAIL_ALREADY_EXISTS;
        }
    }
    return MTM_SUCCESS;
}
static Company findCompany (char* email,EscapeTechnion *EscapeTechnion){


    SET_FOREACH(Company,iterator_comp,(*EscapeTechnion)->company){
        if(strcmp(email,getEmailCompany((Company)iterator_comp))==0){
            return getEmailCompany((Company)iterator_comp;
            }
    }
    return NULL;
}

