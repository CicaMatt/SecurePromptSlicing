#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "user.h"

int main(void) {
    char userName[10]; //user name is 10 characters long
    char email[25]; //email length is 25 characters long
    int socialSecurityNumber; //social security number is integer data type
    
    strcpy(userName,"johndoe");
    strcpy(email,"john.doe@domain.com");
    socialSecurityNumber = 1234;
    
    printf("User Name: %s\n", userName);
    printf("Email Address: %s\n", email);
    printf("Social Security Number: %d\n", socialSecurityNumber);
    
    return 0;
}