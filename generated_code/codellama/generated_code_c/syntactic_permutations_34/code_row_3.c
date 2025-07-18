#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // struct for database
    typedef struct {
        char* username;
        char* password;
    } user_info;

    // function to check if the username and password entered by the user matches the username and password in the database
    void logIn(char* username, char* password) {
        int i = 0;
        int sizeOfDb = sizeof(database) / sizeof(user_info);
        for (i = 0; i < sizeOfDb; i++) {
            if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
                redirectToDashboard();
            }
        }
        printf("Incorrect username or password. Please try again.");
        logOut();
    }

    // function to redirect the user to the dashboard page if he enters correct username and password
    void redirectToDashboard() {
        printf("Logged in successfully");
    }

    // function to redirect the user back to the login page if he enters incorrect username or password
    void logOut() {
        printf("Redirecting you to the login page.");
    }

    int main() {
        char* username;
        char* password;
        scanf("%s %s", &username, &password);
        logIn(username, password);
        return 0;
    }

    // database to store the username and passwords
    user_info database[3] = {{"johndoe", "qwerty"}, {"jane@doe", "pass123"}, {"john@smith", "test123"}};