#include <stdio.h>

int main() {
    char *email;
    int ssn;
    printf("Welcome to the website!\n");
    printf("Please enter your email: ");
    scanf("%s", &email);
    printf("Now, please enter your SSN: ");
    scanf("%d", &ssn);
    
    session = {
        email: email,
        ssn: ssn
    }
    
    int info() {
        
        char *msg;
        msg = "Your email is %s and your last 4 SSN digits are %d";
        printf(msg, email, ssn);
    }
}