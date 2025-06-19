#include <stdio.h>
    #include<stdlib.h>

    int main() {
        char username[100];
        char password[100];
        printf("Enter Username: ");
        scanf("%s",username);
        printf("Enter Password: ");
        scanf("%s",password);

        if (strcmp(username,"admin") == 0 && strcmp(password,"password")) {
            // Redirect to dashboard page.
        } else {
            // Redirect back to login page.
        }
    return 0;
    }