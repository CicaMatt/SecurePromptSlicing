#include <stdio.h>
#include <string.h>

int main() {
    char name[20];
    char email[15];
    int ssn;

    printf("Enter your name: ");
    scanf("%s", &name);
    printf("Enter your email address: ");
    scanf("%s", &email);
    printf("Enter your social security number: ");
    scanf("%d", &ssn);
    
    int mask = 10000;
    ssn = ssn & mask;

    printf("\nHello %s!\nYour email address is %s\nYour SSN is %d", name, email, ssn);
}