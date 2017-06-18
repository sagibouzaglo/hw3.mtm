

#include "company.h"

#define ERROR -1

/**
 * check if the sent email is valid
 *
 * @param email - the company email.
 *
 * @return
 * true - email is valid.
 * false - email is invalid.
 */
static bool IfCompanyEmailValid(char* email);

struct company_t {
    char* email;
    TechnionFaculty Faculty;
    Set rooms;
};

Company companyCreate(char* email,TechnionFaculty faculty,
                                                    CompanyReturn* Result){
    if(!IfCompanyEmailValid(email)){
        *Result= COM_NULL_PARAMETER;
        return NULL;
    }
    Company company = malloc(sizeof(*company));
    if (!company) {
        *Result= COM_OUT_OF_MEMORY;
        return NULL;
    }
    company->email=malloc(sizeof(char)*(strlen(email)+1));
    if (!company->email) {
        companyDestroy(company);
        *Result= COM_OUT_OF_MEMORY;
        return NULL;
    }
    strcpy(company->email,email);
    company->Faculty=faculty;

    company->rooms=setCreate(roomCopy,roomDestroy,roomCompare);///<-void* in room.c
    if(!company->rooms){
        companyDestroy(company);
        *Result= COM_OUT_OF_MEMORY;
        return NULL;
    }
    return company;
}

void companyDestroy(void* company){
    if((((Company)company)->rooms)){
        setDestroy(((Company)company)->rooms);
    }
    free(((Company)company)->email);
    free(company);
}

SetElement companyCopy(void* company){
    if (!company) {
        return NULL;
    }
    CompanyReturn Result=COM_SUCCESS;
    return companyCreate(getEmailCompany((Company)company),
                                getFacultyOfCompany((Company)company),&Result);
}

int companyCompare(void* company1, void* company2){
    assert(company1 && company2);
    return strcmp(getEmailCompany((Company)company1),
                                            getEmailCompany((Company)company2));
}

char* getEmailCompany(Company company){
    assert(company);

    assert(company->email);
    char* emailReturn = malloc(sizeof(char)*(strlen(company->email)+1));
    if(!emailReturn){
        return NULL;
    }
    strcpy(emailReturn,company->email);
    return emailReturn;
}

TechnionFaculty getFacultyOfCompany(Company company){
    assert(company);

    return company->Faculty;
}

Set getCompanyRooms(Company company){
    assert(company);
    return company->rooms;
}

static bool IfCompanyEmailValid(char* email){
    if(!email){
        return NULL;
    }
    int counter=0;
    for(int i=0;i<strlen(email);++i){
        if(*(email+i)=='@'){
            ++counter;
            if(counter>1){
                return false;
            }
        }
    }
    if(counter==1){
        return true;
    }
    return false;
}
