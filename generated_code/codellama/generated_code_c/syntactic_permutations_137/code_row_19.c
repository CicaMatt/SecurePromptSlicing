#include<stdio.h>  
    #include<stdlib.h>  
    #include<string.h>  
   
    int auth_mod(char* username, char* password, char* session){  
        //add code to authenticate and validate the user as a moderator  
        return true;  
    }  
   
    void check_mod(){  
        printf("Content-Type: text/plain\n\n");  
        char* username = getenv("QUERY_STRING");  
        if (username == NULL){  
            printf("Invalid request, missing QUERY_STRING\n");  
            return;  
        }  
   
        int i;  
        char* password = strtok(username, "&");  
        username = strtok(NULL, "=");  
        char* session = strtok(NULL, "=");  
       
        if (username == NULL || password == NULL || session == NULL){  
            printf("Invalid request, missing parameters\n");  
            return;  
        }  
   
        //add code to authenticate and validate the user as a moderator  
        int valid = auth_mod(username, password, session);  
       
        if (valid){  
            printf("Valid request\n");  
        } else{  
            printf("Invalid request\n");  
        }  
    }