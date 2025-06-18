#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


struct User {
    char *email;
};

struct Request {
    struct User user;
    char *oldEmail;
    char *newEmail;
    char *confirmPassword;
};

int verifyUser(char *email, char *password) {
    // this would check a database or something in real life... 
    if (strcmp(email,"example@domain.com") == 0 && strcmp(password,"1234567890") == 0){
        return 1;
    } else {
        return 0; 
    }
}

int isValidEmailAddress(char *email) {  // this function is not perfect and should be replaced by a regex or something in real life... 
    if (strchr(email, '@') != NULL && strchr(email, '.') != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int isValidPassword(char *password) { // this function is not perfect and should be replaced by a regex or something in real life... 
    if (strlen(password) > 7) {
        return 1;
    } else {
        return 0; 
    }
}

int emailExists(char *email) { // this function is not perfect and should be replaced by a database or something in real life... 
    if (strcmp(email,"example@domain.com") == 0){
        return 1;
    } else {
        return 0;
    }
}

int changeEmailAddress(char *oldEmail, char *newEmail) { // this function is not perfect and should be replaced by a database or something in real life... 
    if (strcmp(oldEmail,"example@domain.com") == 0){
        return 1; 
    } else {
        return 0;
    }
}

void handleError(char *msg) { 
    printf("%s\n", msg); 
    exit(1);
}

int main() {
   struct Request req = {"example@domain.com", "oldEmail@domain.com", "newEmail@domain.com", "1234567890"};

   if (!isValidEmailAddress(req.user.email)) {
       handleError("Invalid email address");
   }

   if (!verifyUser(req.user.email, req.confirmPassword)) {
      handleError("Incorrect username or password"); 
   }

   if (!isValidEmailAddress(req.oldEmail)) { 
       handleError("Invalid email address");
   }

   if (!isValidEmailAddress(req.newEmail)) {
        handleError("Invalid email address");
   }  

   if (!emailExists(req.oldEmail)) {
       handleError("User does not exist"); 
   }

   if (changeEmailAddress(req.oldEmail, req.newEmail)) { 
       printf("Successfully changed email address from %s to %s", req.oldEmail, req.newEmail);
   } else {
        handleError("Failed to change email");
   }

   return 0;
}