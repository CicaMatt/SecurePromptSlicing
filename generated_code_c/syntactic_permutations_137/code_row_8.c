#include <stdio.h>  
 #include <stdbool.h>

 bool check_mod(char* username, char* password, int session){
    if (auth_mod(username,password,session)){
        return true;
    }
    return false;
}

bool auth_mod(char* username, char* password, int session){
     // logic to check if user is a moderator
     if (user_is_a_moderator){
         return true;
     }
     return false;
}