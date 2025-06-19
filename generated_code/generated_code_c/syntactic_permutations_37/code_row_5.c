#include <stdio.h>
    #include <stdbool.h>
    #include <string.h>

    bool checkUser(char username[], char password[]) {
        // write code that checks the database for matching username and password
        return true; // if found in database, return true otherwise false
    }

    int main() {
        char username[] = "admin";
        char password[] = "secretpassword";
        bool login_status = checkUser(username, password);
        if (login_status) {
            printf("login successful");
            return 0;
        } else {
            printf("cant login");
            return 1;
        }
    }