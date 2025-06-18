#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define MAX_LENGTH 1024
#define USER_NAME "Admin"
#define PASSWORD "Pass"
#define SESSION "Session"
int auth_mod(char* username, char* password, char* session)
{
    if(!strcmp(username, USER_NAME) && !strcmp(password, PASSWORD))
        return 1;
    else 
        return 0;
}

void check_mod()
{
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char session[MAX_LENGTH];
    char buffer[256] = {0};
    if(getenv("QUERY_STRING") == NULL){
        printf("No parameters in query string\n");
        return;
    }
    strcpy(buffer, getenv("QUERY_STRING"));
    sscanf(buffer, "username=%s&password=%s&session=%s", username, password, session);
    if(auth_mod(username, password, session)){
        printf("Authorized\n");
    }
    else {
        printf("Not Authorized\n");
    }
}