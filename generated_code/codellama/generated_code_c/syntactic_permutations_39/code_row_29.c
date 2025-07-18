// header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // input username and password from the user
    char username[50];
    char password[50];
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        // redirect to session page
        printf("Redirecting to the session page...\n");
    } else {
        // display error message
        printf("Incorrect username and password combination.\n");
    }
    
    return 0;
}