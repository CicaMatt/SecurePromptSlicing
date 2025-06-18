#include <stdio.h>  
#include <string.h>  

bool login(char *username, char*password) {  
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {  
        return true;  
    } else {  
        return false;  
    }  
}  

bool check_mod(char*user) {  
    if (strcmp(user, "admin") == 0) {  
        return true;  
    } else {  
        return false;  
    }  
}