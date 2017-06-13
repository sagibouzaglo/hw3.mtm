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
#define AFTER_DISCOUNT 0.75

#define CHECK_NULL(ptr) if (ptr==NULL){\
                            return MTM_NULL_PARAMETER;\
                            };
static Room findRoom(int roomId,EscapeTechnion *EscapeTechnion);
static MtmErrorCode print_order(FILE *output,Order order,EscapeTechnion *EscapeTechnion);
static MtmErrorCode ifEmailAlreadyExists(char* email,EscapeTechnion *EscapeTechnion);
static Company findCompany (char* email,EscapeTechnion *EscapeTechnion);
static MtmErrorCode ifReservionExistsInComp(Company company,EscapeTechnion *EscapeTechnion);
static MtmErrorCode ifReservionExistsInRoom(Room room ,EscapeTechnion *EscapeTechnion);
static Escaper findEscaper(char* email ,EscapeTechnion *EscapeTechnion);
static void CalculatePrice(Room room ,int* profitFaculty, int num_ppl, Order order,OrderReturn Result);

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
    (*EscapeTechnion)->profit = malloc(sizeof((int)UNKNOWN));
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

MtmErrorCode EscapeTechnion_add_company(char* email,
                                        EscapeTechnion *EscapeTechnion,
                                                    TechnionFaculty faculty){
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

MtmErrorCode EscapeTechnion_remove_company(char* email,
                                                EscapeTechnion *EscapeTechnion){
    CHECK_NULL(EscapeTechnion);
    CHECK_NULL(email);
    Company company = findCompany(email,EscapeTechnion);
    if(company==NULL){
        return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
    }
    if(ifReservionExistsInComp(company,EscapeTechnion)!=MTM_SUCCESS){
        return MTM_RESERVATION_EXISTS;
    }
    setRemove((*EscapeTechnion)->company,company);
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
    SET_FOREACH(Room,roomIterator,getCompanyRooms(company)){
        if(id==getIdRoom(roomIterator)){
            return MTM_ID_ALREADY_EXIST;
        }
    }
    RoomReturn Return;
    Room room = roomCreate(id,price,num_ppl,working_hour,difficulty,&Return);
    if(Return!=ROOM_SUCCESS){
        return (Return == ROOM_INVALID_PARAMETER ? MTM_INVALID_PARAMETER : MTM_OUT_OF_MEMORY);
    }
    setAdd(getCompanyRooms(company),room);
    roomDestroy(room);
    return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_remove_room(TechnionFaculty faculty, int id,
                                                EscapeTechnion *EscapeTechnion){
    if(faculty>UNKNOWN){
        return MTM_INVALID_PARAMETER;
    }
    SET_FOREACH(Company,compIterator,(*EscapeTechnion)->company){
        if(faculty ==(getFacultyOfCompany(compIterator))){
            SET_FOREACH(Room,roomIterator,getCompanyRooms(compIterator)){
                if(id==getIdRoom(roomIterator)){
                    if(ifReservionExistsInRoom(roomIterator ,EscapeTechnion) != MTM_SUCCESS){
                        return MTM_RESERVATION_EXISTS;
                    }
                    setRemove(getCompanyRooms(compIterator),roomIterator);
                    roomDestroy(roomIterator);
                    return MTM_SUCCESS;
                }
            }
        }
    }
    return MTM_ID_DOES_NOT_EXIST;
}

MtmErrorCode EscapeTechnion_add_escaper(char* email,
                                        TechnionFaculty faculty,int skill_level,
                                                EscapeTechnion *EscapeTechnion){

    if(ifEmailAlreadyExists(email,EscapeTechnion)==MTM_EMAIL_ALREADY_EXISTS){
        return MTM_EMAIL_ALREADY_EXISTS;
    }
    EscaperReturn Result;
    Escaper escaper = escaperCreate(email, faculty ,skill_level,&Result);
    if(Result!=Esc_SUCCESS){
        return (Result==Esc_INVALID_PARAMETER? MTM_INVALID_PARAMETER : MTM_OUT_OF_MEMORY);
    }
    setAdd((*EscapeTechnion)->escaper,escaper);
    escaperDestroy(escaper);
    return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_remove_escaper(char* email,EscapeTechnion *EscapeTechnion){
    CHECK_NULL(EscapeTechnion);
    CHECK_NULL(email);
    Escaper escaper = findEscaper(email,EscapeTechnion);
    if(!escaper){
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    EscaperReturn Result;
    LIST_FOREACH(Order,iterator_order,(*EscapeTechnion)->orders){
        char* emailEscaper = getEmailEscaper(getEscaperOrder((Order)iterator_order),&Result);
        if (Result!=Esc_SUCCESS){
            return NULL;
        }
        if(strcmp(email,emailEscaper)==0){
            orderDestroy(iterator_order);
            listRemoveCurrent((*EscapeTechnion)->orders);

        }
    }
    return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_add_order(char* email,TechnionFaculty faculty, int id,
                                      char* time, int num_ppl,
                                       EscapeTechnion *EscapeTechnion){
    CHECK_NULL(EscapeTechnion);
    CHECK_NULL(email);
    if(!IfEmailValid(email)){
        return MTM_INVALID_PARAMETER;
    }
    Escaper escaper = findEscaper(email,EscapeTechnion);
    if(!escaper){
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    OrderReturn Result;

    listInsertFirst((*EscapeTechnion)->orders,orderCreate(time, escaper, num_ppl
                                   ,findCompany(email,EscapeTechnion),id, &Result));
   return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_day(){

   return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_best_faculty(){

   return MTM_SUCCESS;
}

static MtmErrorCode ifEmailAlreadyExists(char* email,
                                                EscapeTechnion *EscapeTechnion){
   CHECK_NULL(email);
   CHECK_NULL(EscapeTechnion);

    SET_FOREACH(Company,iterator_comp,(*EscapeTechnion)->company){
        if(strcmp(email,getEmailCompany((Company)iterator_comp))==0){
            return MTM_EMAIL_ALREADY_EXISTS;
        }
    }
    EscaperReturn Result;
    LIST_FOREACH(Order,iterator_order,(*EscapeTechnion)->orders){
        char* emailCompany =
                getEmailEscaper(getEscaperOrder((Order)iterator_order),&Result);
        char* emailEscaper = getEmailEscaper(getEscaperOrder((Order)iterator_order),&Result);
        if (Result!=ORD_SUCCESS){
            return (Result==ORD_OUT_OF_MEMORY ? MTM_OUT_OF_MEMORY :
                                                            MTM_NULL_PARAMETER);
        }
        if(strcmp(email,emailEscaper)==0){
            return MTM_EMAIL_ALREADY_EXISTS;
        }
    }
    return MTM_SUCCESS;
}
static Company findCompany (char* email,EscapeTechnion *EscapeTechnion){


    SET_FOREACH(Company,iterator_comp,(*EscapeTechnion)->company){
        if(strcmp(email,getEmailCompany((Company)iterator_comp))==0){
            return ((Company)iterator_comp);
            }
    }
    return NULL;
}

static MtmErrorCode ifReservionExistsInComp(Company company,
                                                EscapeTechnion *EscapeTechnion){
    SET_FOREACH(Room,roomIterator,getCompanyRooms(company)) {
        LIST_FOREACH(Order, iterator_order, (*EscapeTechnion)->orders) {
            if(getRoomIdOrder(iterator_order)==getIdRoom(roomIterator)){
                return MTM_RESERVATION_EXISTS;
            }
        }
    }
    return MTM_SUCCESS;
}
static MtmErrorCode ifReservionExistsInRoom(Room room ,
                                                EscapeTechnion *EscapeTechnion){

    LIST_FOREACH(Order, iterator_order, (*EscapeTechnion)->orders) {
        if(roomCompare((Room)getRoomIdOrder(iterator_order),(Room)getIdRoom(room))){
            return MTM_RESERVATION_EXISTS;
        }
    }
    return MTM_SUCCESS;
}

static Room findRoom(int roomId,EscapeTechnion *EscapeTechnion){
   }
static Escaper findEscaper(char* email ,EscapeTechnion *EscapeTechnion){
    EscaperReturn Result;
    LIST_FOREACH(Order,iterator_order,(*EscapeTechnion)->orders){
        char* emailEscaper = getEmailEscaper(getEscaperOrder((Order)iterator_order),&Result);
        if (Result!=Esc_SUCCESS){
            return NULL;
        }
        if(strcmp(email,emailEscaper)==0){
            return getEscaperOrder((Order)iterator_order);
        }
    }
    return NULL;
}
static void CalculatePrice(Room room ,int* profitFaculty, int num_ppl, Order order,OrderReturn Result) {
    assert(escaper && profitFaculty && room && order);
    if (getFacultyOfCompany(getCompanyOrder(order)) ==
        getFacultyEscaper(getEscaperOrder(order))) {
        order->tot_price = (int) (num_ppl * (getPriceRoom(room)) *
                                  AFTER_DISCOUNT);
    } else {
        order->tot_price = num_ppl * (getPriceRoom(room));
    }
}
MtmErrorCode technion_report_day(FILE* output, EscapeTechnion *EscapeTechnion){
    List tmp1=listCreate(orderCopy,orderDestroy),
                    tmp2=listCreate(orderCopy,orderDestroy);
//  tmp1= listFilter((*EscapeTechnion)->orders, <#FilterListElement filterElement#>, <#ListFilterKey key#>)
//  tmp2= listFilter((*EscapeTechnion)->orders, <#FilterListElement filterElement#>, <#ListFilterKey key#>)
    listDestroy((*EscapeTechnion)->orders);
    (*EscapeTechnion)->orders=tmp2;
    Order order= listGetCurrent((*EscapeTechnion)->orders);
    LIST_FOREACH(Order, Order_iterator, tmp1){
        print_order(output,order,EscapeTechnion);
        order=listGetNext((*EscapeTechnion)->orders);
    }
    listDestroy(tmp1);
    (*EscapeTechnion)->day++;
}

static MtmErrorCode order_filter(){
    return MTM_SUCCESS;
}
/**

 */

static MtmErrorCode print_order(FILE *output,Order order,EscapeTechnion *EscapeTechnion){
    Escaper escaper = getEscaperOrder(order);
    Company company = getCompanyOrder(order);
    int roomId = getRoomIdOrder(order);
    Room Room = findRoom(roomId, EscapeTechnion);
    EscaperReturn *escaperResult;
    char *email = getEmailEscaper(escaper, escaperResult),
                    *companyEmail = getEmailCompany(company);
    int skill_level= getSkillLevel(escaper),id = getIdRoom(Room),
                    time = getTimeOrder(order),
                        difficulty=getDifficultyRoom(Room),
    num_ppl = getNumPOrder(order), tot_price= getPriceOrder(order);
    TechnionFaculty Faculty = getFacultyEscaper(escaper),
                    companyFaculty = getFacultyOfCompany(company);
    
    mtmPrintOrder(output,email,skill_level,Faculty,companyEmail,companyFaculty,
                        id,time,difficulty,num_ppl,tot_price);
    

    return MTM_SUCCESS;
}
