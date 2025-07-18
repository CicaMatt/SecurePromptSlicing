#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    int main() {
        char username[20];
        char password[20];
        printf("Enter Username\n");
        fgets(username, 19, stdin);
        printf("Enter Password\n");
        fgets(password, 19, stdin);
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            printf("Successfully Logged In!\n");
        } else {
            printf("Incorrect Username or Password. Try again.\n");
        main();
    }
}