#include <stdio.h>

int main() {
    char username[100], old_email[50], new_email[50];
    int password;
    
    printf("Enter your username: ");
    scanf("%s", &username);
    printf("Enter your old email: ");
    scanf("%s", &old_email);
    printf("Enter your new email: ");
    scanf("%s", &new_email);
    printf("Enter your password: ");
    scanf("%d", &password);
    
    if(strcmp(username, old_email) == 0 && strcmp(old_email, new_email) != 0 && password == correct_password){
        printf("Email changed successfully");
    } else {
        printf("Invalid username and/or password");
    }
}