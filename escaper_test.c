//
//  escaper_test.c
//  hw3
//
//  Created by sagi bouzaglo on 18/06/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

//#include "list_mtm/test_utilities.h"
//#include "../Room.h"
#include "test_utilities.h"
#include "escaper.h"
#include <string.h>

static bool testEscaperCreate() {
    EscaperReturn Result=Esc_SUCCESS;
    ASSERT_TEST(escaperCreate(NULL, UNKNOWN, 0,&Result) == NULL);
    ASSERT_TEST(Result==Esc_NULL_PARAMETER);
    ASSERT_TEST(escaperCreate("test", UNKNOWN, 0,&Result) == NULL);
    ASSERT_TEST(Result==Esc_INVALID_PARAMETER);
    return true;
}

static bool testEscaperCopy() {
    EscaperReturn Result=Esc_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&Result);
    ASSERT_TEST(escaperCopy(NULL)==NULL);
    Escaper escaper_cpy=escaperCopy(escaper);
    ASSERT_TEST(escaperEquals(escaper,escaper_cpy)==0);
    escaperDestroy(escaper);
    escaperDestroy(escaper_cpy);
    return true;
}

static bool testEscaperEquals() {
    EscaperReturn Result=Esc_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&Result);
    Escaper escaper2 = escaperCreate("test@test.com",0,0,&Result);
    ASSERT_TEST(escaperEquals(escaper,escaper2)==0);
    escaperDestroy(escaper2);
    Escaper escaper3 = escaperCreate("t@test.com",0,0,&Result);
    ASSERT_TEST(escaperEquals(escaper,escaper3)==0);
    escaperDestroy(escaper3);
    Escaper escaper4 = escaperCreate("testest@test.com",0,0,&Result);
    ASSERT_TEST(escaperEquals(escaper,escaper4)==0);
    escaperDestroy(escaper4);
    escaperDestroy(escaper);
    return true;
}

static bool testGetEmailEscaper(){
    EscaperReturn Result=Esc_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&Result);
    ASSERT_TEST(strcmp(getEmailEscaper(escaper),"test@test.com")==0);
    escaperDestroy(escaper);
    return true;
}

static bool testGetSkillLevel(){
    EscaperReturn Result=Esc_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&Result);
    ASSERT_TEST(getFacultyEscaper(escaper)==0);
    escaperDestroy(escaper);
    return true;
}

static bool testGetFacultyEscaper(){
    EscaperReturn Result=Esc_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&Result);
    ASSERT_TEST(getFacultyEscaper(NULL)==UNKNOWN);
    ASSERT_TEST(getFacultyEscaper(escaper)==0);
    escaperDestroy(escaper);
    return true;
}

static bool testEscaperDestroy(){
    EscaperReturn Result=Esc_SUCCESS;
    Escaper escaper = escaperCreate("test@test.com",0,0,&Result);
    escaperDestroy(escaper);
    return true;
}

int main (int argv, char** arc){
    RUN_TEST(testEscaperCreate);
    RUN_TEST(testEscaperCopy);
    RUN_TEST(testEscaperEquals);
    RUN_TEST(testGetEmailEscaper);
    RUN_TEST(testGetSkillLevel);
    RUN_TEST(testGetFacultyEscaper);
    RUN_TEST(testEscaperDestroy);
    return 0;
}

