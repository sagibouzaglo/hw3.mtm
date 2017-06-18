//
//  company_test.c
//  hw3
//
//  Created by sagi bouzaglo on 18/06/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "test_utilities.h"
#include "company.h"
#include <string.h>

static bool testCompanyCreate(){
    CompanyReturn Result;
    ASSERT_TEST(companyCreate(NULL, 0, &Result)==NULL);
    ASSERT_TEST(Result == COM_NULL_PARAMETER);
    return true;
}

static bool testCompanyCopy(){
    ASSERT_TEST(companyCopy(NULL)==NULL);
    CompanyReturn Result;
    char* email = {"test@"} ;
    Company company = companyCreate(email, 0, &Result);
    Company company2 = companyCopy(company);
    ASSERT_TEST(companyCompare(company, company2)==0);
    companyDestroy(company);
    companyDestroy(company2);
    return true;
}

static bool testCompanyCompare(){
    CompanyReturn Result;
    char* email = {"test@"} ;
    Company company = companyCreate(email, 0, &Result);
    ASSERT_TEST(Result==COM_SUCCESS);
    Company company2 = companyCreate(email, 0, &Result);
    ASSERT_TEST(Result==COM_SUCCESS);
    ASSERT_TEST(companyCompare(company, company2)==0);
    companyDestroy(company);
    companyDestroy(company2);
    return true;
}

static bool testEmailCompany(){
    CompanyReturn Result;
    char* email = {"test@"} ;
    Company company = companyCreate(email, 0, &Result);
    ASSERT_TEST(Result==COM_SUCCESS);
    ASSERT_TEST(strcmp(getEmailCompany(company),email)==0);
    companyDestroy(company);
    return true;
}

static bool testFacultyOfCompany(){
    CompanyReturn Result;
    char* email = {"test@"} ;
    Company company = companyCreate(email, 0, &Result);
    ASSERT_TEST(Result==COM_SUCCESS);
    ASSERT_TEST(getFacultyOfCompany(company)==0);
    companyDestroy(company);
    return true;
}

static bool testGetCompanyRooms(){
    CompanyReturn Result;
    char* email = {"test@"} ;
    Company company = companyCreate(email, 0, &Result);
    ASSERT_TEST(Result==COM_SUCCESS);
    ASSERT_TEST(getCompanyRooms(company)!=NULL);
    companyDestroy(company);
    return true;
}

static bool testCompanyDestroy(){
    CompanyReturn Result;
    char* email = {"test@"} ;
    Company company = companyCreate(email, 0, &Result);
    companyDestroy(company);
    return true;
}

int main (int argv, char** arc){
    RUN_TEST(testCompanyCreate);
    RUN_TEST(testCompanyCopy);
    RUN_TEST(testCompanyCompare);
    RUN_TEST(testEmailCompany);
    RUN_TEST(testFacultyOfCompany);
    RUN_TEST(testGetCompanyRooms);
    RUN_TEST(testCompanyDestroy);
    return 0;
}
