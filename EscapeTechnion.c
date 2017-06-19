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

/**
 *  add the earning from a room order to the relevant faculty.
 *
 * @param faculty - the faculty owns the room.
 * @param priceOrder -  the earning from the room.
 * @param escapeTechnion1 -  the system ADT.
 *
 */
static void InsertPriceToFaculty(TechnionFaculty faculty,
                                 int priceOrder,EscapeTechnion escapeTechnion1);

/**
 *  calculate the recommended room.
 *
 * @param room - the room we check.
 * @param escaper -  the escaper ordering the room.
 * @param num_ppl -  number of people ordering the room.
 *
 * @return
 * int - value of recommendation for the room
 *
 */
static int CalculationOfRecommendation(Room room,Escaper escaper,int num_ppl);

/**
 *  get the system day.
 *
 * @param EscTechnion -  the system ADT.
 *
 * @return
 * int- system day
 *
 */
static int getDayEtechnion(EscapeTechnion EscTechnion);

/**
 *  check if the order is for the given day.
 *
 * @param order -  and order.
 * @param day - the day we check.
 *
 * @return
 * true - the order is for the checked day.
 * false - the order is not for the checked day.
 *
 */
static bool orderDayEqualFilter(ListElement order, ListFilterKey day);

/**
 *  check if the order is not for the given day.
 *
 * @param order -  and order.
 * @param day - the day we check.
 *
 * @return
 * false - the order is for the checked day.
 * true - the order is not for the checked day.
 *
 */
static bool orderDayNotEqualFilter(ListElement order, ListFilterKey day);

/**
 *  check if escaper is inside a room.
 *
 * @param faculty -  faculty of the escaper .
 * @param id - the room id.
 * @param EscapeTechnion - the system ADT.
 * @param hour - hour of the order for escaper.
 * @param day - day of the order for escaper.
 *
 * @return
 * false - the escaper is not in the room.
 * true - the escaper is in the room.
 *
 */
static bool isClientInRoom(TechnionFaculty faculty,int id,
                                EscapeTechnion EscapeTechnion,int hour,int day);

/**
 *  check if the room is available in the given day and hour.
 *
 * @param faculty -  faculty of the escaper .
 * @param id - the room id.
 * @param EscapeTechnion - the system ADT.
 * @param hour - hour of the order for escaper.
 * @param day - day of the order for escaper.
 *
 * @return
 * false - the room is not available.
 * true - the room is available.
 *
 */
static bool isRoomAvalable(TechnionFaculty faculty,int id,
                                EscapeTechnion EscapeTechnion,int hour,int day);

/**
 *  check the closest time the sent room is available.
 *
 * @param room -  and order.
 * @param faculty -  faculty of the escaper.
 * @param escapeTechnion - the system ADT.
 *
 * @return
 * time - closest time the room available.
 * NULL -
 */
static char* closestTimeAvailableRoom(Room room,TechnionFaculty faculty,
                                                EscapeTechnion escapeTechnion);

/**
 *  search for the company owns the room email.
 *
 * @param id_room -  the room id.
 * @param faculty - room faculty.
 * @param EscapeTechnion - the system ADT.
 *
 * @return
 * char* - the company searched mail.
 * NULL - the company doesn't exist.
 */
static char* findEmailCompany(int id_room,TechnionFaculty faculty,
                                                EscapeTechnion EscapeTechnion);

/**
 *  search for the company email.
 *
 * @param roomId -  the room id.
 * @param Faculty - the room faculty.
 * @param EscapeTechnion - the system ADT.
 *
 * @return
 * Room - the searched room.
 * NULL - room not found.
 *
 */
static Room findRoom(int roomId,TechnionFaculty Faculty,
                                            EscapeTechnion EscapeTechnion);

/**
 *  search for the company match the sent email.
 *
 * @param email -  the company email.
 * @param EscapeTechnion1 - the system ADT.
 *
 * @return
 * Company - the searched company.
 * NULL - company not found.
 *
 */
static Company findCompany (char* email,EscapeTechnion EscapeTechnion1);

/**
 *  search for the escaper match the sent email.
 *
 * @param email -  the escaper email.
 * @param EscapeTechnion - the system ADT.
 *
 * @return
 * Escaper - the searched escaper.
 * NULL - escaper not found.
 *
 */
static Escaper findEscaper(char* email ,EscapeTechnion EscapeTechnion);

/**
 * check if email already exist
 *
 * @param email -  the searched email.
 * @param EscapeTechnion - the system ADT.
 *
 * @return
 * MTM_EMAIL_ALREADY_EXISTS - email already exist.
 * MTM_OUT_OF_MEMORY - allocation failed.
 * MTM_SUCCESS - email dosen't exist.
 *
 */
static MtmErrorCode ifEmailAlreadyExists(char* email,
                                                EscapeTechnion EscapeTechnion);

/**
 *  check if a room owned by the company is reserved.
 *
 * @param company -  the company we searce in.
 * @param EscapeTechnion - the system ADT.
 *
 * @return
 * MTM_RESERVATION_EXISTS - the searched room is reserved.
 * MTM_SUCCESS - reservasion dosen't exist.
 *
 */
static MtmErrorCode ifReservionExistsInComp(Company company,
                                                EscapeTechnion EscapeTechnion);

/**
 *  check if a room owned by the faculty is reserved.
 *
 * @param room -  the company we searce in.
 * @param faculty -  the faculty owns the room.
 * @param EscapeTechnion - the system ADT.
 *
 * @return
 * MTM_RESERVATION_EXISTS - the searched room is reserved.
 * MTM_SUCCESS - reservasion dosen't exist.
 *
 */
static MtmErrorCode ifReservionExistsInRoom(Room room ,TechnionFaculty faculty,
                                                EscapeTechnion EscapeTechnion);

/**
 *  print the given order.
 *
 * @param output -  the output channel.
 * @param order -  the order channek.
 * @param EscapeTechnion - the system ADT.
 *
 * @return
 * MTM_OUT_OF_MEMORY - allocation failed.
 * MTM_SUCCESS - order printed.
 *
 */
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
    char* mail = {"escaper2@gmail.com"};
    if(strcmp(email,mail)==0){
        mail=NULL;
    }
    Escaper escaper = findEscaper(email,EscapeTechnion);
    if(!escaper){
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    List newOrder = listFilter(EscapeTechnion->orders,orderEscaperFilter,(ListFilterKey)email);
    listDestroy(EscapeTechnion->orders);
    EscapeTechnion->orders=newOrder;
    setRemove(EscapeTechnion->escaper,escaper);
    return MTM_SUCCESS;
}

static bool orderEscaperFilter(ListElement order,ListFilterKey email){
    assert(order && email);
    return (strcmp(((char *) email),getEmailEscaper(getEscaperOrder((Order)order))) != 0);
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
    if ((id<0)||(faculty<0)){
        return MTM_INVALID_PARAMETER;
    }
    Room room = findRoom(id,faculty,EscapeTechnion);
    if(!room){
        return MTM_ID_DOES_NOT_EXIST;
    }
    char* company_email = findEmailCompany(id,faculty,EscapeTechnion);
    Company company = findCompany(company_email,EscapeTechnion);
    free(company_email);
    if(!company) return MTM_OUT_OF_MEMORY;
    Order order = orderCreate(time, escaper, num_ppl,
                            company,id, &Result,EscapeTechnion->day);
    if(Result!=ORD_SUCCESS) {
        if (Result != ORD_NO_ROOMS_AVAILABLE) {
            return Result == ORD_OUT_OF_MEMORY ? MTM_OUT_OF_MEMORY
                                                    : MTM_NULL_PARAMETER;
        } else return MTM_NO_ROOMS_AVAILABLE;
    }
    if(isClientInRoom(escaper,EscapeTechnion,getHourOrder(order),
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
    //LIST_FOREACH(Order,itr,currentDayOrders){
     //   printf("report day currentDayOrders ---> order: %s day:%d currDay: %d\n",(getEmailEscaper(getEscaperOrder((Order)itr))),getDayOrder(itr),currentDay);
    //}
    if(!currentDayOrders){
        return MTM_OUT_OF_MEMORY;
    }
    List newOrdersList = listFilter(EscapeTechnion1->orders,
                                    orderDayNotEqualFilter,
                                    &currentDay);
   // LIST_FOREACH(Order,itr,newOrdersList){
  //      printf("report day newOrdersList ---> order: %s day:%d currDay: %d\n",(getEmailEscaper(getEscaperOrder((Order)itr))),getDayOrder(itr),currentDay);
  //  }
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
    ++EscapeTechnion1->day;
    return MTM_SUCCESS;
}

static MtmErrorCode print_order(FILE *output,Order order,
                                                EscapeTechnion EscapeTechnion1){
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
        if (*(EscapeTechnion1->profit+i)!=*(EscapeTechnion1->profit +
                                           bestFaculty[FIRST])) {
            if (*(EscapeTechnion1->profit + i) > *(EscapeTechnion1->profit +
                                                   bestFaculty[FIRST])) {
                bestFaculty[THIRD] = bestFaculty[SECOND];
                bestFaculty[SECOND] = bestFaculty[FIRST];
                bestFaculty[FIRST] = i;

            } else if (*(EscapeTechnion1->profit+i)!=*(EscapeTechnion1->profit + bestFaculty[SECOND])){
                if((*(EscapeTechnion1->profit+i)>*(EscapeTechnion1->profit + bestFaculty[SECOND]))) {
                    bestFaculty[THIRD] = bestFaculty[SECOND];
                    bestFaculty[SECOND] = i;
                } else if((*(EscapeTechnion1->profit+i)>*(EscapeTechnion1->profit + bestFaculty[THIRD]))){
                    bestFaculty[THIRD]=i;
                 }

                }
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
    int bestScore=-1;
    int numFacultyBestScore=0;
    Room recommendRoom=NULL;
    int idRoom =-1;
    SET_FOREACH(Company,iterator_comp,escapeTechnion->companies){
        SET_FOREACH(Room,roomCompIterator,getCompanyRooms(iterator_comp)){
            int Comparison_index=CalculationOfRecommendation(roomCompIterator,
                                                               escaper,num_ppl);


            if ((Comparison_index<bestScore)||(bestScore==-1)){
                bestScore=Comparison_index;
                numFacultyBestScore=getFacultyOfCompany(iterator_comp);
                recommendRoom=roomCompIterator;
                idRoom = getIdRoom(recommendRoom);
                continue;
            } else if(Comparison_index==bestScore){
                int distansFaculty =
                        (abs(getFacultyOfCompany(iterator_comp)-
                                        getFacultyEscaper(escaper))-
                                            abs(numFacultyBestScore-
                                                getFacultyEscaper(escaper)));
                if(distansFaculty>0) continue;
                if (distansFaculty<0 ||
                            (distansFaculty==0 &&
                                getFacultyOfCompany(iterator_comp)<
                                                        numFacultyBestScore)) {
                    bestScore = Comparison_index;
                    numFacultyBestScore = (int) getFacultyOfCompany(
                            iterator_comp);
                    recommendRoom = roomCompIterator;
                    idRoom = getIdRoom(recommendRoom);
                } else if(getFacultyOfCompany(iterator_comp)==numFacultyBestScore){
                        if(idRoom > getIdRoom(roomCompIterator)) {
                            bestScore = Comparison_index;
                            numFacultyBestScore = (int) getFacultyOfCompany(
                                    iterator_comp);
                            recommendRoom = roomCompIterator;
                            idRoom = getIdRoom(recommendRoom);
                        }
                }
            }
        }
    }
    return EscapeTechnion_add_escaper_order(email,
                (TechnionFaculty)numFacultyBestScore,idRoom,
                    closestTimeAvailableRoom(recommendRoom,
                        (TechnionFaculty)numFacultyBestScore,escapeTechnion),
                           num_ppl,escapeTechnion);
}

static char* closestTimeAvailableRoom(Room room,TechnionFaculty faculty,
                                      EscapeTechnion escapeTechnion){
    for(int day=escapeTechnion->day; day>=0 ;++day){
        for(int hour=getOpenHRoom(room);hour<getCloseHRoom(room);++hour){

           if(isRoomAvalable(faculty,getIdRoom(room),escapeTechnion,hour,day)){
               day-=escapeTechnion->day;
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
  // day+=EscapeTechnion->day;
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
        if(getOpenHRoom(room)>hour ||  getCloseHRoom(room)<=hour){
            return false;
        }
    }
    return true;
}

static bool isClientInRoom(Escaper escaper,
                           EscapeTechnion EscapeTechnion,int hour,int day){

    LIST_FOREACH(Order,iteratorOrder,EscapeTechnion->orders){
        if(escaperEquals(escaper,getEscaperOrder(iteratorOrder))==0 && getHourOrder(iteratorOrder)==hour && getDayOrder(iteratorOrder)==day){
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

    int DAY = *((int*)day);
    int dayOrder = getDayOrder((Order)order);
    return (dayOrder == DAY);
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

