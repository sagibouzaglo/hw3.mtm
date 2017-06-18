//
//  EscapeTechnion.c
//  hw3
//
//  Created by sagi bouzaglo on 28/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#define FIRST 0
#define SECOND 1
#define THIRD 2
#define THREE_BEST_FACULTIES 3
#define AFTER_DISCOUNT 0.75
#include "EscapeTechnion.h"
#define CHECK_NULL(ptr) if (ptr==NULL){\
                            return MTM_NULL_PARAMETER;\
                            };
#define ReturnSetResult(setRes) if(setRes!=SET_SUCCESS){\
                                    switch(SetReturn){\
                                        case SET_OUT_OF_MEMORY :\
                                            return MTM_OUT_OF_MEMORY;\
                                        case SET_NULL_ARGUMENT :\
                                            return MTM_INVALID_PARAMETER;\
                                        case SET_ITEM_ALREADY_EXISTS:\
                                            return MTM_EMAIL_ALREADY_EXISTS;\
                                        case SET_ITEM_DOES_NOT_EXIST :\
                                            return MTM_INVALID_PARAMETER;\
                                        default: break;\
                                    }\
                                };
#define ReturnListResult(ListRes) if(ListRes!=LIST_SUCCESS){\
                                    switch(ListRes){\
                                        case LIST_OUT_OF_MEMORY :\
                                            return MTM_OUT_OF_MEMORY;\
                                        case LIST_NULL_ARGUMENT :\
                                            return MTM_NULL_PARAMETER;\
                                        case LIST_INVALID_CURRENT :\
                                            return MTM_INVALID_PARAMETER;\
                                        default: break;\
                                    }\
                                };


static void InsertPriceToFaculty(TechnionFaculty faculty,
                                 int priceOrder,EscapeTechnion escapeTechnion1);
static int CalculationOfRecommendation(Room room,Escaper escaper,int num_ppl);
static int getDayEtechnion(EscapeTechnion EscTechnion);
static bool orderDayEqualFilter(ListElement order, ListFilterKey day);
static bool orderDayNotEqualFilter(ListElement order, ListFilterKey day);
static bool isClientInRoom(TechnionFaculty faculty,int id,
                                EscapeTechnion EscapeTechnion,int hour,int day);
static bool isRoomAvalable(TechnionFaculty faculty,int id,
                                EscapeTechnion EscapeTechnion,int hour,int day);
static char* closestTimeAvailableRoom(Room room,TechnionFaculty faculty,
                                                EscapeTechnion escapeTechnion);
static char* findEmailCompany(int id_room,TechnionFaculty faculty,
                                                EscapeTechnion EscapeTechnion);
static Room findRoom(int roomId,TechnionFaculty Faculty,
                                            EscapeTechnion EscapeTechnion);
static Company findCompany (char* email,EscapeTechnion EscapeTechnion1);
static Escaper findEscaper(char* email ,EscapeTechnion EscapeTechnion);
static MtmErrorCode ifEmailAlreadyExists(char* email,
                                                EscapeTechnion EscapeTechnion);
static MtmErrorCode ifReservionExistsInComp(Company company,
                                                EscapeTechnion EscapeTechnion);
static MtmErrorCode ifReservionExistsInRoom(Room room ,TechnionFaculty faculty,
                                                EscapeTechnion EscapeTechnion);
static MtmErrorCode print_order(FILE *output,Order order,
                                            EscapeTechnion EscapeTechnion);

struct escapetechnion {
    Set companies;
    Set escaper;
    List orders;
    int day;
    int* profit;
};


MtmErrorCode create_EscapeTechnion(EscapeTechnion* EscapeTechnion1){
    *EscapeTechnion1 = malloc(sizeof(*(*EscapeTechnion1)));
    if(!*EscapeTechnion1){
      return MTM_OUT_OF_MEMORY;
    }
    (*EscapeTechnion1)->companies = setCreate(companyCopy,
                                                companyDestroy,companyCompare);
    if(!(*EscapeTechnion1)->companies) {
        destroy_EscapeTechnion(*EscapeTechnion1);
        return MTM_OUT_OF_MEMORY;
    }
    (*EscapeTechnion1)->escaper = setCreate(escaperCopy,
                                                escaperDestroy,escaperEquals);
    if(!(*EscapeTechnion1)->escaper) {
        destroy_EscapeTechnion(*EscapeTechnion1);
        return MTM_OUT_OF_MEMORY;
    }
    (*EscapeTechnion1)->orders = listCreate(orderCopy,orderDestroy);
    if(!(*EscapeTechnion1)->orders) {
        destroy_EscapeTechnion(*EscapeTechnion1);
        return MTM_OUT_OF_MEMORY;
    }
    (*EscapeTechnion1)->profit = malloc(sizeof(int)*UNKNOWN);
    if(!(*EscapeTechnion1)->profit) {
        destroy_EscapeTechnion(*EscapeTechnion1);
        return MTM_OUT_OF_MEMORY;
    }
   for(int i=0;i<UNKNOWN;++i){
       ((*EscapeTechnion1)->profit)[i]=0;
    }
    (*EscapeTechnion1)->day=0;
    return MTM_SUCCESS;
}

void destroy_EscapeTechnion(EscapeTechnion EscapeTechnion1){
    assert(EscapeTechnion1);
    setDestroy(EscapeTechnion1->companies);
    setDestroy(EscapeTechnion1->escaper);
    listDestroy(EscapeTechnion1->orders);
    free(EscapeTechnion1->profit);
    free(EscapeTechnion1);
}

MtmErrorCode EscapeTechnion_add_company(char* email,
                                            EscapeTechnion EscapeTechnion1,
                                                       TechnionFaculty faculty){
    if(!email || !EscapeTechnion1){
        return MTM_NULL_PARAMETER;
    }
    MtmErrorCode check_email = ifEmailAlreadyExists(email,EscapeTechnion1);
    if(check_email!=MTM_SUCCESS){
        return check_email;
    }
    CompanyReturn Result=COM_SUCCESS;
    Company  company1 = companyCreate(email,faculty,&Result);
    if(Result!=COM_SUCCESS) {
        return Result == COM_NULL_PARAMETER ? MTM_NULL_PARAMETER
                                                    : MTM_OUT_OF_MEMORY;
    }
    SetResult SetReturn = setAdd (EscapeTechnion1->companies, (void*)company1);
    ReturnSetResult(SetReturn);
    companyDestroy(company1);
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
    SetResult SetReturn = setRemove(EscapeTechnion->companies,company);
    ReturnSetResult(SetReturn);
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
    Set roomsCompany = getCompanyRooms(company);
    if(roomsCompany==NULL) {
        return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
    }
        SET_FOREACH(Room,roomIterator,roomsCompany){
        if(id==getIdRoom(roomIterator)){
            return MTM_ID_ALREADY_EXIST;
        }
    }
    RoomReturn Return=ROOM_SUCCESS;
    Room room = roomCreate(id,price,num_ppl,working_hour,difficulty,&Return);
    if(Return!=ROOM_SUCCESS){
        return (Return == ROOM_INVALID_PARAMETER ? MTM_INVALID_PARAMETER
                                                    : MTM_OUT_OF_MEMORY);
    }
    SetResult SetReturn=(setAdd(getCompanyRooms(company),room));
    ReturnSetResult(SetReturn);
    roomDestroy(room);
    return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_remove_room(TechnionFaculty faculty, int id,
                                                EscapeTechnion EscapeTechnion){
    if(faculty>UNKNOWN){
        return MTM_INVALID_PARAMETER;
    }
    SET_FOREACH(Company , compIterator ,EscapeTechnion->companies){
        if(faculty ==(getFacultyOfCompany(compIterator))){
            SET_FOREACH(Room,roomIterator,getCompanyRooms(compIterator)){
                if(id==getIdRoom(roomIterator)){
                    if(ifReservionExistsInRoom(roomIterator,faculty,
                                               EscapeTechnion) != MTM_SUCCESS){
                        return MTM_RESERVATION_EXISTS;
                    }
                    SetResult SetReturn=setRemove(getCompanyRooms(compIterator),
                                                                  roomIterator);
                    ReturnSetResult(SetReturn);
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
    EscaperReturn Result=Esc_SUCCESS;
    Escaper escaper = escaperCreate(email, faculty ,skill_level,&Result);
    if(Result!=Esc_SUCCESS){
        return (Result == Esc_INVALID_PARAMETER ? MTM_INVALID_PARAMETER
                                                    : MTM_OUT_OF_MEMORY);
    }
    SetResult SetReturn=setAdd(EscapeTechnion->escaper,escaper);

    escaperDestroy(escaper);
    ReturnSetResult(SetReturn);
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
    LIST_FOREACH(Order,iterator_order,EscapeTechnion->orders){
        char* emailEscaper = getEmailEscaper(
                                        getEscaperOrder((Order)iterator_order));
        if (!emailEscaper){
            return MTM_NULL_PARAMETER;
        }
        if(strcmp(email,emailEscaper)==0){
            free(emailEscaper);
            ReturnListResult(listRemoveCurrent(EscapeTechnion->orders));
        }
    }
    return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_add_escaper_order(char* email,
                                                TechnionFaculty faculty, int id,
                                                    char* time, int num_ppl,
                                                EscapeTechnion EscapeTechnion){
    CHECK_NULL(EscapeTechnion);
    CHECK_NULL(email);
    if ( IfEscaperEmailValid(email)==false){
        return MTM_INVALID_PARAMETER;
    }
    Escaper escaper = findEscaper(email,EscapeTechnion);
    if(!escaper){
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    OrderReturn Result=ORD_SUCCESS;
    Room room = findRoom(id,faculty,EscapeTechnion);
    if(!room){
        return MTM_ID_DOES_NOT_EXIST;
    }
    char* company_email = findEmailCompany(id,faculty,EscapeTechnion);
    Company company = findCompany(company_email,EscapeTechnion);
    free(company_email);
    if(!company) return MTM_OUT_OF_MEMORY;
    Order order = orderCreate(time, escaper, num_ppl,
                            company,id, &Result);
    if(Result!=ORD_SUCCESS) {
        if (Result != ORD_NO_ROOMS_AVAILABLE) {
            return Result == ORD_OUT_OF_MEMORY ? MTM_OUT_OF_MEMORY
                                                    : MTM_NULL_PARAMETER;
        } else return MTM_NO_ROOMS_AVAILABLE;
    }
    if(isClientInRoom(faculty,id,EscapeTechnion,getHourOrder(order),
                                                    getDayOrder(order))){
        orderDestroy(order);
        return MTM_CLIENT_IN_ROOM;
    }
    if(!isRoomAvalable(faculty,id,EscapeTechnion,getHourOrder(order),
                                                        getDayOrder(order))){
        orderDestroy(order);
        return MTM_ROOM_NOT_AVAILABLE;
    }
    ReturnListResult(listInsertFirst(EscapeTechnion->orders,order));
    orderDestroy(order);
    return MTM_SUCCESS;
}

static char* findEmailCompany(int id_room,TechnionFaculty faculty,
                                                EscapeTechnion EscapeTechnion){
    assert(EscapeTechnion);
    Set companies = EscapeTechnion->companies;
    if(!companies)
        return NULL;
    SET_FOREACH(Company, company_iterator, companies){
        Set rooms = getCompanyRooms(company_iterator);
        if(!rooms) return NULL;
        TechnionFaculty faculty_iterator= getFacultyOfCompany(company_iterator);
        if (faculty_iterator == faculty){
            SET_FOREACH(Room, room_iterator, rooms){
                if(id_room == getIdRoom(room_iterator)){
                    return getEmailCompany(company_iterator);
                }
            }
        }
    }
    return NULL;
}

static MtmErrorCode ifEmailAlreadyExists(char* email,
                                                EscapeTechnion EscapeTechnion) {
    CHECK_NULL(email);
    CHECK_NULL(EscapeTechnion);
    if (setGetSize(EscapeTechnion->companies)) {
        SET_FOREACH(Company, iterator_comp, (EscapeTechnion)->companies) {
            if (strcmp(email, getEmailCompany((Company) iterator_comp)) == 0) {
                return MTM_EMAIL_ALREADY_EXISTS;
            }
        }
        if (setGetSize(EscapeTechnion->companies)) {
            LIST_FOREACH(Order, iterator_order, EscapeTechnion->orders) {
                char *emailEscaper = getEmailEscaper(
                        getEscaperOrder((Order) iterator_order));
                if (!emailEscaper) {
                    return  MTM_OUT_OF_MEMORY ;
                }
                if (strcmp(email, emailEscaper) == 0) {
                    return MTM_EMAIL_ALREADY_EXISTS;
                }
            }
        }
    }
    return MTM_SUCCESS;
}
static Company findCompany (char* email,EscapeTechnion EscapeTechnion){
    Set companies = (EscapeTechnion)->companies;
    if(!companies)        return NULL;
    SET_FOREACH(Company , iterator_comp,companies){
        if(strcmp(email,getEmailCompany(iterator_comp))==0){
            return (iterator_comp);
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
        if(findRoom(getRoomIdOrder(iterator_order),faculty,EscapeTechnion),room){
            return MTM_RESERVATION_EXISTS;
        }
    }
    return MTM_SUCCESS;
}

static Room findRoom(int roomId,TechnionFaculty Faculty,
                                                EscapeTechnion EscapeTechnion){
    SET_FOREACH(Company, company_iterator, EscapeTechnion->companies){
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
    assert(EscapeTechnion && email);
    Set escapers = EscapeTechnion->escaper;
    if(!escapers) return NULL;
    SET_FOREACH(Escaper ,iterator_escaper ,escapers){
        char* emailEscaper = getEmailEscaper(iterator_escaper);
        if(strcmp(email,emailEscaper)==0){
            free(emailEscaper);
            return iterator_escaper;
        }
        free(emailEscaper);
    }
    return NULL;
}

MtmErrorCode technion_report_day(FILE* output, EscapeTechnion EscapeTechnion1){
    assert(EscapeTechnion1);
    int currentDay = getDayEtechnion(EscapeTechnion1);
    List currentDayOrders = listFilter(EscapeTechnion1->orders,
                                       orderDayEqualFilter,
                                       &currentDay);
    if(!currentDayOrders){
        return MTM_OUT_OF_MEMORY;
    }
    List newOrdersList = listFilter(EscapeTechnion1->orders,
                                    orderDayNotEqualFilter,
                                    &currentDay);
    if(!newOrdersList){
        return MTM_OUT_OF_MEMORY;
    }
    listDestroy(EscapeTechnion1->orders);
    EscapeTechnion1->orders=newOrdersList;
    ReturnListResult(listSort(currentDayOrders, compareOrders));
    mtmPrintDayHeader(output, currentDay,listGetSize(currentDayOrders));
    LIST_FOREACH(Order , Order_iterator, currentDayOrders){
        InsertPriceToFaculty(getFacultyOfCompany(getCompanyOrder(Order_iterator))
                ,getPriceOrder(Order_iterator),EscapeTechnion1);
        print_order(output,Order_iterator,EscapeTechnion1);
    }
    mtmPrintDayFooter(output, currentDay);
    listDestroy(currentDayOrders);
    EscapeTechnion1->day++;
    return MTM_SUCCESS;
}


static MtmErrorCode print_order(FILE *output,Order order,EscapeTechnion EscapeTechnion1){
    assert(EscapeTechnion1);
    Escaper escaper = getEscaperOrder(order);
    assert(escaper);
    Company company = getCompanyOrder(order);
    assert(company);
    TechnionFaculty Faculty = getFacultyEscaper(escaper),
                companyFaculty = getFacultyOfCompany(company);
    int roomId = getRoomIdOrder(order);
    assert(roomId);
    Room Room = findRoom(roomId, companyFaculty,EscapeTechnion1);
    assert(Room);
    char* email = getEmailEscaper(escaper);
    if(!email){
        return MTM_OUT_OF_MEMORY;
    }
    char* companyEmail = getEmailCompany(company);
    if(!companyEmail){
        free(email);
        return MTM_OUT_OF_MEMORY;
    }
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

MtmErrorCode technion_report_best(FILE *output,EscapeTechnion EscapeTechnion1){
    if(!EscapeTechnion1){
        return MTM_NULL_PARAMETER;
    }
    int* bestFaculty=malloc(sizeof(int)*THREE_BEST_FACULTIES);
    if(!bestFaculty){
        return MTM_OUT_OF_MEMORY;
    }
    for(int i=0; i<THREE_BEST_FACULTIES;++i) {
      *(bestFaculty+i)=i;
    }
    for(int i=0; i<UNKNOWN;++i){
        if(*(EscapeTechnion1->profit+i)>*(EscapeTechnion1->profit +
                                                           bestFaculty[FIRST])){
            bestFaculty[THIRD]=bestFaculty[SECOND];
            bestFaculty[SECOND]=bestFaculty[FIRST];
            bestFaculty[FIRST]=i;
            continue;
        }
        if(*(EscapeTechnion1->profit+i)>*(EscapeTechnion1->profit +
                                                          bestFaculty[SECOND])){
            bestFaculty[THIRD]=bestFaculty[SECOND];
            bestFaculty[SECOND]=i;
            continue;
        }
        if(*(EscapeTechnion1->profit+i)>*(EscapeTechnion1->profit +
                                                           bestFaculty[THIRD])){
            bestFaculty[THIRD]=i;
            continue;
        }
    }
    int totalRevenue = 0;
    for(int i = 0; i < UNKNOWN; i++) {
        totalRevenue += EscapeTechnion1->profit[i];
    }
    mtmPrintFacultiesHeader(output, UNKNOWN,EscapeTechnion1->day, totalRevenue);
    mtmPrintFaculty(output,(TechnionFaculty)bestFaculty[FIRST],
                                   EscapeTechnion1->profit[bestFaculty[FIRST]]);
    mtmPrintFaculty(output,(TechnionFaculty)bestFaculty[SECOND],
                                  EscapeTechnion1->profit[bestFaculty[SECOND]]);
    mtmPrintFaculty(output,(TechnionFaculty)bestFaculty[THIRD],
                                   EscapeTechnion1->profit[bestFaculty[THIRD]]);
    mtmPrintFacultiesFooter(output);
    free(bestFaculty);
    return MTM_SUCCESS;
}

MtmErrorCode EscapeTechnion_add_escaper_recommend(char* email, int num_ppl,
                                                 EscapeTechnion escapeTechnion){
    if(!IfEscaperEmailValid(email)){
        return MTM_INVALID_PARAMETER;
    }
    Escaper escaper = findEscaper(email,escapeTechnion);
    if(!escaper){
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    int maxScore=0;
    int numFacultyMaxScore=0;
    Room recommendRoom=NULL;
    SET_FOREACH(Company,iterator_comp,escapeTechnion->companies){
        SET_FOREACH(Room,roomCompIterator,getCompanyRooms(iterator_comp)){
            int Comparison_index=CalculationOfRecommendation(roomCompIterator,
                                                               escaper,num_ppl);
            if(Comparison_index>maxScore){
                maxScore=Comparison_index;
                numFacultyMaxScore=(int)getFacultyOfCompany(iterator_comp);
                recommendRoom=roomCompIterator;
                continue;
            } else if(Comparison_index==maxScore){
                int distansFaculty =
                        (abs(getFacultyOfCompany(iterator_comp)-
                                        getFacultyEscaper(escaper))-
                                            abs(numFacultyMaxScore-
                                                getFacultyEscaper(escaper)));
                if(distansFaculty>0) continue;
                else if (distansFaculty<0 ||
                            (distansFaculty==0 &&
                                getFacultyOfCompany(iterator_comp)<
                                                        numFacultyMaxScore)){
                    maxScore=Comparison_index;
                    numFacultyMaxScore=(int)getFacultyOfCompany(iterator_comp);
                    recommendRoom=roomCompIterator;
                }
            }
        }
    }
    return EscapeTechnion_add_escaper_order(email,
                (TechnionFaculty)numFacultyMaxScore,getIdRoom(recommendRoom),
                    closestTimeAvailableRoom(recommendRoom,
                        (TechnionFaculty)numFacultyMaxScore,escapeTechnion),
                           num_ppl,escapeTechnion);
}

static char* closestTimeAvailableRoom(Room room,TechnionFaculty faculty,
                                      EscapeTechnion escapeTechnion){
    for(int day=escapeTechnion->day; day>=0 ;++day){
        for(int hour=getOpenHRoom(room);hour<getCloseHRoom(room);++hour){
           if(isRoomAvalable(faculty,getIdRoom(room),escapeTechnion,hour,day)){
               char* time=malloc(sizeof(char)*5);
               if(!time) return NULL;
               sprintf(time, "%d-%d",day,hour);
               return time;
           }
        }
    }
    return NULL;
}

static int CalculationOfRecommendation(Room room,Escaper escaper,int num_ppl){
    assert(room && escaper);
    int arg1 = (getNumPplRoom(room)-num_ppl);
    arg1 *= arg1;
    int arg2 = (getDifficultyRoom(room)-getSkillLevel(escaper));
    arg2 *= arg2;
    return (arg1+arg2);
}
static bool isRoomAvalable(TechnionFaculty faculty,int id,
                           EscapeTechnion EscapeTechnion,int hour,int day){
    LIST_FOREACH(Order,iteratorOrder,(EscapeTechnion)->orders){
        if(getFacultyOfCompany(getCompanyOrder(iteratorOrder))==faculty &&
                                    getRoomIdOrder(iteratorOrder)==id &&
                                        getHourOrder(iteratorOrder)==hour &&
                                            getDayOrder(iteratorOrder)==day){
            return false;
        }
        Room room = findRoom(id,faculty,EscapeTechnion);
        if(!room){
            return false;
        }
        if(getOpenHRoom(room)<hour ||  getCloseHRoom(room)<hour){
            return false;
        }
    }
    return true;
}

static bool isClientInRoom(TechnionFaculty faculty,int id,
                           EscapeTechnion EscapeTechnion,int hour,int day){
    LIST_FOREACH(Order,iteratorOrder,EscapeTechnion->orders){
        if(getFacultyOfCompany(getCompanyOrder(iteratorOrder))==faculty &&
                                    getRoomIdOrder(iteratorOrder)==id &&
                                        getHourOrder(iteratorOrder)==hour &&
                                            getDayOrder(iteratorOrder)==day){
            return true;
        }
    }
    return false;
}

static int getDayEtechnion(EscapeTechnion EscTechnion){
    assert(EscTechnion);
    return (EscTechnion->day);
}

static bool orderDayEqualFilter(ListElement order, ListFilterKey day){
    assert(order && day);
    return getDayOrder(order) == *((int*)day);
}

static bool orderDayNotEqualFilter(ListElement order, ListFilterKey day){
    if (getDayOrder(order)!=*((int*)day)){
        return true;
    }
    return false;
}

static void InsertPriceToFaculty(TechnionFaculty faculty,int priceOrder,
                                            EscapeTechnion escapeTechnion1){
    ((escapeTechnion1)->profit)[faculty] += priceOrder;
}

