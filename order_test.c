//
//  order_test.c
//  hw3
//
//  Created by sagi bouzaglo on 18/06/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "test_utilities.h"
#include "order.h"
#include <string.h>


static bool testOrderCreate() {
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    ASSERT_TEST(orderCreate(time, NULL, 0, company, 0, &Result)==NULL);
    ASSERT_TEST(orderCreate(time, escaper, 0, NULL, 0, &Result)==NULL);
    Order order = orderCreate(time, NULL, 0, company, 0, &Result);
    ASSERT_TEST(order!=NULL);
    orderDestroy(order);
    ASSERT_TEST(orderCreate(0, 0, 0, NULL, 0, &Result) == NULL);
    ASSERT_TEST(Result==ROOM_INVALID_PARAMETER);
    return true;
}

static bool testOrderCopy(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    Order order2 = orderCopy(order);
    ASSERT_TEST(compareOrders(order, order2)==0);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    orderDestroy(order2);
    return true;
}

static bool testCompareOrders(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    char* time2="0-2";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    Order order2 = orderCreate(time2, escaper, 0, company, 0, &Result);
    ASSERT_TEST(compareOrders(order, order2)==-1);
    ASSERT_TEST(compareOrders(order2, order)==1);
    orderDestroy(order2);
    Company company2 = companyCreate("test@", 2, &compResult);
    Order order3 = orderCreate(time, escaper, 0, company2, 0, &Result);
    ASSERT_TEST(compareOrders(order, order3)==-1);
    ASSERT_TEST(compareOrders(order3, order)==1);
    orderDestroy(order3);
    companyDestroy(company2);
    Order order4 = orderCreate(time, escaper, 0, company, 0, &Result);
    ASSERT_TEST(compareOrders(order, order4)==-1);
    ASSERT_TEST(compareOrders(order4, order)==1);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    orderDestroy(order4);
    return true;
}

static bool testOrderEqualRoom(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    Order order2 = orderCreate(time, escaper, 0, company, 0, &Result);
    ASSERT_TEST(orderEqualsRoom(order, order2)==0);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    orderDestroy(order2);
    return true;
}

static bool testOrderEqualsEscaper(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    Order order2 = orderCreate(time, escaper, 0, company, 0, &Result);
    ASSERT_TEST(orderEqualsEscaper(order, order2)==0);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    orderDestroy(order2);
    return true;
}

static bool testGetPriceOrder(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    ASSERT_TEST(getPriceOrder(order)==0);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    return true;
}

static bool testPutPriceOrer(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    putPriceOrder(&order, 0);
    ASSERT_TEST(order->tot_price ==0);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    return true;
}

static bool testGetTimeOrder(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    ASSERT_TEST(strcmp(getTimeOrder(order),time)==0);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    return true;
}

static bool testGetHourOrder(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    ASSERT_TEST(getHourOrder(order)==1);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    return true;
}

static bool testGetNumPOrder(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    ASSERT_TEST(getNumPOrder(order)==0);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    return true;
}

static bool testGetRoomIdOrder(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    ASSERT_TEST(getRoomIdOrder(order)==0);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    return true;
}

static bool testGetEscaperOrder(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    ASSERT_TEST(getEscaperOrder(order)==escaper);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    return true;
}

static bool testGetCompanyOrder(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    ASSERT_TEST(getCompanyOrder(order)==company);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    return true;
}

static bool testGetDayOrder(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    ASSERT_TEST(getDayOrder(order)==0);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    return true;
}

static bool testOrderDestroy(){
    OrderReturn Result=ORD_SUCCESS;
    EscaperReturn escResult=Esc_SUCCESS;
    CompanyReturn compResult=COM_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&escResult);
    Company company = companyCreate("test@", 0, &compResult);
    char* time="0-1";
    Order order = orderCreate(time, escaper, 0, company, 0, &Result);
    companyDestroy(company);
    escaperDestroy(escaper);
    orderDestroy(order);
    return true;
}

int main (int argv, char** arc){
    RUN_TEST(testOrderCreate);
    RUN_TEST(testOrderCopy);
    RUN_TEST(testCompareOrders);
    RUN_TEST(testOrderEqualRoom);
    RUN_TEST(testOrderEqualsEscaper);
    RUN_TEST(testGetPriceOrder);
    RUN_TEST(testPutPriceOrer);
    RUN_TEST(testGetTimeOrder);
    RUN_TEST(testGetHourOrder);
    RUN_TEST(testGetNumPOrder);
    RUN_TEST(testGetRoomIdOrder);
    RUN_TEST(testGetEscaperOrder);
    RUN_TEST(testGetCompanyOrder);
    RUN_TEST(testGetDayOrder);
    RUN_TEST(testOrderDestroy);
    return 0;
}
