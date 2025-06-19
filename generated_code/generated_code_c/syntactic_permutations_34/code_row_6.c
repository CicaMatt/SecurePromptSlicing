#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char username[256];
    char password[256];
    
    printf("Enter Username : ");
    scanf("%s", username);
    
    printf("Enter Password : ");
    scanf("%s", password);
    
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        printf("\nLogin Successful!\nRedirecting to Dashboard...\n");
    } else {
        printf("\nInvalid Credentials!\nRedirecting back to Login Page...\n");
    }
    
    return 0;
}