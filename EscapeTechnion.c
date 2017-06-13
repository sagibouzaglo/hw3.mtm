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
static bool orderDayEqualFilter(ListElement order, ListFilterKey day);
static bool orderDayNotEqualFilter(ListElement order, ListFilterKey day);
static Room findRoom(int roomId,TechnionFaculty Faculty,EscapeTechnion EscapeTechnion);
static MtmErrorCode print_order(FILE *output,Order order,EscapeTechnion EscapeTechnion);
static MtmErrorCode ifEmailAlreadyExists(char* email,EscapeTechnion EscapeTechnion);
static Company findCompany (char* email,EscapeTechnion EscapeTechnion);
static MtmErrorCode ifReservionExistsInComp(Company company,EscapeTechnion EscapeTechnion);
static MtmErrorCode ifReservionExistsInRoom(Room room ,TechnionFaculty faculty,EscapeTechnion EscapeTechnion);
static Escaper findEscaper(char* email ,EscapeTechnion EscapeTechnion);
static void CalculatePrice(Room room , int num_ppl, Order order,OrderReturn Result);


struct escapetechnion {
    int day;
    Set company;
    Set escaper;
    List orders;
    int* profit;
};

MtmErrorCode create_EscapeTechnion(EscapeTechnion *EscapeTechnion){
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

MtmErrorCode destroy_EscapeTechnion(EscapeTechnion EscapeTechnion){
   CHECK_NULL(EscapeTechnion);
   free(EscapeTechnion->profit);
   free(EscapeTechnion);
   return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_add_company(char* email,
                                        EscapeTechnion EscapeTechnion,
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
                                                EscapeTechnion EscapeTechnion){
    CHECK_NULL(EscapeTechnion);
    CHECK_NULL(email);
    Company company = findCompany(email,EscapeTechnion);
    if(company==NULL){
        return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
    }
    if(ifReservionExistsInComp(company,EscapeTechnion)!=MTM_SUCCESS){
        return MTM_RESERVATION_EXISTS;
    }
    setRemove(EscapeTechnion->company,company);
    companyDestroy(company);
    return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_add_room(char* email,int id, int price, int num_ppl,
                                     char* working_hour, int difficulty,
                                     EscapeTechnion EscapeTechnion){
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
                                                EscapeTechnion EscapeTechnion){
    if(faculty>UNKNOWN){
        return MTM_INVALID_PARAMETER;
    }
    SET_FOREACH(Company,compIterator,EscapeTechnion->company){
        if(faculty ==(getFacultyOfCompany(compIterator))){
            SET_FOREACH(Room,roomIterator,getCompanyRooms(compIterator)){
                if(id==getIdRoom(roomIterator)){
                    if(ifReservionExistsInRoom(roomIterator ,faculty,EscapeTechnion) != MTM_SUCCESS){
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
                                                EscapeTechnion EscapeTechnion){

    if(ifEmailAlreadyExists(email,EscapeTechnion)==MTM_EMAIL_ALREADY_EXISTS){
        return MTM_EMAIL_ALREADY_EXISTS;
    }
    EscaperReturn Result;
    Escaper escaper = escaperCreate(email, faculty ,skill_level,&Result);
    if(Result!=Esc_SUCCESS){
        return (Result==Esc_INVALID_PARAMETER? MTM_INVALID_PARAMETER : MTM_OUT_OF_MEMORY);
    }
    setAdd(EscapeTechnion->escaper,escaper);
    escaperDestroy(escaper);
    return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_remove_escaper(char* email,
                                                EscapeTechnion EscapeTechnion){
    CHECK_NULL(EscapeTechnion);
    CHECK_NULL(email);
    Escaper escaper = findEscaper(email,EscapeTechnion);
    if(!escaper){
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    EscaperReturn Result;
    LIST_FOREACH(Order,iterator_order,EscapeTechnion->orders){
        char* emailEscaper = getEmailEscaper(getEscaperOrder((Order)iterator_order),&Result);
        if (Result!=Esc_SUCCESS){
            return MTM_NULL_PARAMETER;
        }
        if(strcmp(email,emailEscaper)==0){
            orderDestroy(iterator_order);
            listRemoveCurrent(EscapeTechnion->orders);

        }
    }
    return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_add_order(char* email,TechnionFaculty faculty, int id,
                                      char* time, int num_ppl,
                                       EscapeTechnion EscapeTechnion){
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
    Room room = findRoom(id,faculty,EscapeTechnion);
    if(!room){
        return MTM_ID_DOES_NOT_EXIST;
    }

    Order order=orderCreate(time, escaper, num_ppl,
                            findCompany(email,EscapeTechnion),id, &Result);
    CalculatePrice(findRoom(id,faculty,EscapeTechnion),num_ppl,order,Result);
    listInsertFirst(EscapeTechnion->orders,orderCreate(time, escaper, num_ppl
                                   ,findCompany(email,EscapeTechnion),id, &Result));
    orderDestroy(order);

    return MTM_SUCCESS;
}

static MtmErrorCode ifEmailAlreadyExists(char* email,
                                                EscapeTechnion EscapeTechnion){
   CHECK_NULL(email);
   CHECK_NULL(EscapeTechnion);

    SET_FOREACH(Company,iterator_comp,(EscapeTechnion)->company){
        if(strcmp(email,getEmailCompany((Company)iterator_comp))==0){
            return MTM_EMAIL_ALREADY_EXISTS;
        }
    }
    EscaperReturn Result;
    LIST_FOREACH(Order,iterator_order,EscapeTechnion->orders){
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
static Company findCompany (char* email,EscapeTechnion EscapeTechnion){


    SET_FOREACH(Company,iterator_comp,(EscapeTechnion)->company){
        if(strcmp(email,getEmailCompany((Company)iterator_comp))==0){
            return ((Company)iterator_comp);
            }
    }
    return NULL;
}

static MtmErrorCode ifReservionExistsInComp(Company company,
                                                EscapeTechnion EscapeTechnion){
    SET_FOREACH(Room,roomIterator,getCompanyRooms(company)) {
        LIST_FOREACH(Order, iterator_order, (EscapeTechnion)->orders) {
            if(getRoomIdOrder(iterator_order)==getIdRoom(roomIterator)){
                return MTM_RESERVATION_EXISTS;
            }
        }
    }
    return MTM_SUCCESS;
}
static MtmErrorCode ifReservionExistsInRoom(Room room ,TechnionFaculty faculty,
                                                EscapeTechnion EscapeTechnion){
    LIST_FOREACH(Order, iterator_order, (EscapeTechnion)->orders) {
        if(findRoom(getRoomIdOrder(iterator_order),faculty,EscapeTechnion),room))){
            return MTM_RESERVATION_EXISTS;
        }
    }
    return MTM_SUCCESS;
}

static Room findRoom(int roomId,TechnionFaculty Faculty,
                                                EscapeTechnion EscapeTechnion){
    SET_FOREACH(Company, company_iterator, EscapeTechnion->company){
        TechnionFaculty tmp = getFacultyOfCompany(company_iterator);
        if (tmp == Faculty){
            Set rooms = getCompanyRooms(company_iterator);
            SET_FOREACH(Room, room_iterator,rooms ){
                int id = getIdRoom(room_iterator);
                if(id == roomId){
                    return room_iterator;
                }
            }
        }
    }
    return NULL;
}

static Escaper findEscaper(char* email ,EscapeTechnion EscapeTechnion){
    EscaperReturn Result;
    LIST_FOREACH(Order,iterator_order,(EscapeTechnion)->orders){
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
static void CalculatePrice(Room room , int num_ppl, Order order,OrderReturn Result) {
    assert( room && order);
    if (getFacultyOfCompany(getCompanyOrder(order)) ==
        getFacultyEscaper(getEscaperOrder(order))) {
        putPriceOrder(order,(int) (num_ppl * (getPriceRoom(room)) *
                                  AFTER_DISCOUNT));
    } else {
        putPriceOrder(order,num_ppl * (getPriceRoom(room)));
    }
}

/**

 */
MtmErrorCode technion_report_day(FILE* output, EscapeTechnion EscapeTechnion){
    CHECK_NULL(EscapeTechnion);
    List currentDayOrders = listFilter(EscapeTechnion->orders,
                                                orderDayEqualFilter,
                                                (void*)&EscapeTechnion->day);
    List newOrdersList = listFilter(EscapeTechnion->orders,
                                            orderDayNotEqualFilter,
                                                (void*)&EscapeTechnion->day);
    listDestroy((EscapeTechnion)->orders);
    (EscapeTechnion)->orders=newOrdersList;
    listSort(currentDayOrders, compareOrders);
    LIST_FOREACH(Order, Order_iterator, currentDayOrders){
        print_order(output,Order_iterator,EscapeTechnion);
    }
    listDestroy(currentDayOrders);
    EscapeTechnion->day++;
}

/**

 */
static bool orderDayEqualFilter(ListElement order, ListFilterKey day){
    if (getDayOrder(order)==(int)day){
        return true;
    }
    
    return false;
}

static bool orderDayNotEqualFilter(ListElement order, ListFilterKey day){
    if (getDayOrder(order)!=(int)day){
        return true;
    }
    return false;
}

/**

 */
static MtmErrorCode print_order(FILE *output,Order order,EscapeTechnion EscapeTechnion){
    CHECK_NULL(EscapeTechnion);
    Escaper escaper = getEscaperOrder(order);
    assert(escaper);
    Company company = getCompanyOrder(order);
    assert(company);
    TechnionFaculty Faculty = getFacultyEscaper(escaper),
                companyFaculty = getFacultyOfCompany(company);
    int roomId = getRoomIdOrder(order);
    assert(roomId);
    Room Room = findRoom(roomId, companyFaculty,EscapeTechnion);
    assert(Room);
    EscaperReturn *escaperResult;
    char *email = getEmailEscaper(escaper, escaperResult),
                    *companyEmail = getEmailCompany(company);
    assert(*email && *companyEmail);
    int skill_level= getSkillLevel(escaper),id = getIdRoom(Room),
                    time = getHourOrder(order),
                        difficulty=getDifficultyRoom(Room),
                                    num_ppl = getNumPOrder(order),
                                            tot_price= getPriceOrder(order);
    assert(skill_level && time && difficulty && num_ppl && tot_price);
    mtmPrintOrder(output,email,skill_level,Faculty,companyEmail,companyFaculty,
                        id,time,difficulty,num_ppl,tot_price);
    return MTM_SUCCESS;
}
static bool isRoomAvalable(TechnionFaculty faculty,int id,EscapeTechnion EscapeTechnion,int hour,int day){
    LIST_FOREACH(Order,iteratorOrder,(EscapeTechnion)->orders){
        if(getFacultyOfCompany(getCompanyOrder(iteratorOrder))==faculty && getRoomIdOrder(iteratorOrder)==id
                && getHourOrder(iteratorOrder)==hour && getDayOrder(iteratorOrder)==day){
            return false;
        }
        if(getOpenHRoom(findRoom(id,faculty,EscapeTechnion))<hour || getCloseHRoom(findRoom(id,faculty,EscapeTechnion))<hour){
            return false;
        }
    }
    return true;
}
static bool isClientInRoom(TechnionFaculty faculty,int id,EscapeTechnion EscapeTechnion,int hour,int day){
    LIST_FOREACH(Order,iteratorOrder,(EscapeTechnion)->orders){
        if(getFacultyOfCompany(getCompanyOrder(iteratorOrder))==faculty && getRoomIdOrder(iteratorOrder)==id
           && getHourOrder(iteratorOrder)==hour && getDayOrder(iteratorOrder)==day){
            return false;
        }
    }
    return true;
}
