#include <stdio.h>
#include <string.h>

void info(){
    char *username = "Bob";
    char *email = "bob@example.com";
    int ssn = 123456789;
    printf("Username: %s\n", username);
    printf("Email: %s\n", email);
    printf("SSN(last 4 digits): %d\n", ssn%10000);
}