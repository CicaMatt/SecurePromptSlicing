#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

char *check_mod(char *session) {  
    return auth_mod(session);  
}  

char *auth_mod(char *session) {  
   char* user = get_user_from_session(session);
    if (strcmp(user, "moderator") == 0){  
      return "true";  
    } else {  
      return "false";  
    }  
}  

char *get_user_from_session(char *session) {  
   char* user = get_user_info(session, "user");  
   if (user == NULL){  
      return "guest";  
   }  else {  
      return user;  
   }  
}  

char *get_user_info(char *session, char *key) {  
   // code to get the user info from a database or other storage
}