
#include "escaper.h"
#include "set.h"

#define CHECK_NULL(ptr) if (!ptr){\
                            return MTM_NULL_PARAMETER;\
                            };

#define ERROR -1


struct escaper {
    char* email;
    TechnionFaculty Faculty;
    int skill_level;
};


/** Allocates a new escaper */
Escaper escaperCreate(char* email, TechnionFaculty faculty , int skill_level,
                                                    EscaperReturn* Result){
    if(!IfEscaperEmailValid(email)){
        *Result= Esc_INVALID_PARAMETER;
        return NULL;
    }
    Escaper escaper = malloc(sizeof(*escaper));
    if (!escaper) {
        *Result= Esc_OUT_OF_MEMORY;
        return NULL;
    }
    escaper->email=malloc((sizeof(char)*strlen(email))+1);
    if (!escaper->email) {
        *Result= Esc_OUT_OF_MEMORY;
        return NULL;
    }
    strcpy(escaper->email,email);
    escaper->Faculty=faculty;
    escaper->skill_level=skill_level;
    return escaper;
}

/** Frees an existing escaper object */
void escaperDestroy(void* escaper){
    free(((Escaper)escaper)->email);
    free(escaper);
}

/** Allocates a new escaper which is a copy of the argument */
SetElement escaperCopy(void* escaper){
    if (!escaper) {
        return NULL;
    }
    EscaperReturn Result=Esc_SUCCESS;
    return escaperCreate(((Escaper)escaper)->email,((Escaper)escaper)->Faculty,
                         ((Escaper)escaper)->skill_level, &Result);
}

/** Returns true if both email escaper are identical */
int escaperEquals(void* escaper1, void* escaper2) {
    assert(escaper1 && escaper2);
    return strcmp(getEmailEscaper((Escaper)escaper1),getEmailEscaper((Escaper)escaper2));
}

char* getEmailEscaper(Escaper escaper){
    if(!escaper){
        return NULL;
    }
    char* emailReturn = malloc(sizeof(strlen(escaper->email)+1));
    if(!emailReturn){
        return NULL;
    }
    strcpy(escaper->email,emailReturn);
    return emailReturn;
}
int getSkillLevel(Escaper escaper){
    if(!escaper){
        return ERROR;
    }
    return escaper->skill_level;
}

TechnionFaculty getFacultyEscaper(Escaper escaper){
    if(!escaper){
        return UNKNOWN;
    }
    return escaper->Faculty;
}
bool IfEscaperEmailValid(char* email) {
    if (!email) {
        return NULL;
    }
    int counter = 0;
    for (int i = 0; i < strlen(email); ++i) {
        if (*(email + i) == '@') {
            ++counter;
            if (counter > 1) {
                return false;
            }
        }
    }
    if (counter == 1) {
        return true;
    }
    return false;
}

