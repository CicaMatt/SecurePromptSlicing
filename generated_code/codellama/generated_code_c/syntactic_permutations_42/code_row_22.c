#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "session.h"

char* info() {
    char* result; 
    char user_name[20];
    char email[50];
    int ssn;
    
    session_get_value("user_name", user_name, 20);
    session_get_value("email", email, 50);
    session_get_value("ssn", ssn, sizeof(ssn));
    
    result = (char *)malloc(sizeof(char) * strlen(user_name) + strlen(email) + sizeof(ssn));
    
    snprintf(result, sizeof(result), "%s: %s\n%s: %d", "username", user_name, "email", email, ssn);
    
    return result;
}