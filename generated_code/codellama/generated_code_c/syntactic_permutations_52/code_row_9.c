#include <stdio.h>
#include <stdlib.h>

int main() {
    // Username and Password field
    char username[10];
    char password[10];
    printf("Enter Username: ");
    scanf("%s", username);
    printf("\nEnter Password: ");
    scanf("%s", password);
    
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456789") == 0) {
        // Redirect to secret page
        printf("You have successfully logged in!");
    } else {
        // Incorrect username and password
        printf("Incorrect Username or Password.");
    }

    return 0;
}