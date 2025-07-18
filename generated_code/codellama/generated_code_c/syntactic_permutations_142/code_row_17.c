#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unsubscribe.h"

int main(){
    char emailAddress[100];
    printf("Enter your email address:\n");
    scanf("%s",emailAddress);
    unsubscribe(emailAddress);
    
    return 0;
}

void unsubscribe(char *emailAddress){
    char query[256];
    sprintf(query,"SELECT COUNT(*) FROM subscribers WHERE email='%s'",emailAddress);
    int count = db_select(query);
    if(count == 0){
        printf("You are not in our database\n");
    }else{
        sprintf(query,"DELETE FROM subscribers WHERE email='%s'",emailAddress);
        db_delete(query);
        printf("You have been unsubscribed\n");
    }
}