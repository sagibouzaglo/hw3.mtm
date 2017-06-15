

#include "company.h"

#define ERROR -1
static bool IfCompanyEmailValid(char* email);

struct company_t {
    char* email;
    TechnionFaculty Faculty;
    Set rooms;
};


/** Allocates a new company */
Company companyCreate(char* email, TechnionFaculty faculty,CompanyReturn* Result){
    if(!IfCompanyEmailValid(email)){
        *Result= COM_NULL_PARAMETER;
        return NULL;
    }
    Company company = malloc(sizeof(*company));
    if (!company) {
        *Result= COM_OUT_OF_MEMORY;
        return NULL;
    }
    company->email=malloc((sizeof(char)*strlen(email))+1);
    if (!company->email) {
        *Result= COM_OUT_OF_MEMORY;
        return NULL;
    }
    strcpy(company->email,email);
    company->Faculty=faculty;

    company->rooms=setCreate(roomCopy,roomDestroy,roomCompare); ///<-void* in room.c
    if(!company->rooms){
        *Result= COM_OUT_OF_MEMORY;
        return  NULL;
    }
    return company;
}

/** Frees an existing company object */
void companyDestroy(void* company){
    setDestroy(((Company)company)->rooms);
    free(((Company)company)->email);
    free(company);
}

/** Allocates a new company which is a copy of the argument */
SetElement companyCopy(void* company){
    if (!company) {
        return NULL;
    }
    CompanyReturn Result;
    return companyCreate(getEmailCompany((Company)company),getFacultyOfCompany((Company)company),&Result);
}
/** Returns 0 if both email company are identical */
int companyCompare(void* company1, void* company2){
    assert(company1 && company2);
    return strcmp(getEmailCompany((Company)company1),getEmailCompany((Company)company2));
}
char* getEmailCompany(Company company){
    if(!company){
        return NULL;
    }
    char* emailReturn = malloc(sizeof(strlen(company->email)+1));
    if(!emailReturn){
        return NULL;
    }
    strcpy(company->email,emailReturn);
    return emailReturn;
}

TechnionFaculty getFacultyOfCompany(Company company){
    if(!company){
        return UNKNOWN;
    }
    return company->Faculty;
}

Set getCompanyRooms(Company company){
    if(!company){
        return NULL;
    }
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
