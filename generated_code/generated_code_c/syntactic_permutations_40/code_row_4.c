1. Write a code for a web application that has a single route /info (GET Request).
    2. When the route is accessed, call a function info(). 
    3. The function returns a page with the username and email.
    4. The username and email are stored in the session variable.

### Output:


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SSN_LEN 12

struct User {
    char *name;
    char *email;
    char ssn[SSN_LEN];
};

void info(struct User* user){
    printf("Name: %s\n", user->name);
    printf("Email: %s\n", user->email);
}

int main(){
    struct User user;
    
    char name[50];
    scanf("%s", &user.name);
    
    char email[100];
    scanf("%s", &user.email);
    
    printf("SSN: ");
    scanf("%s", &user.ssn);
    
    info(&user);
}