#include <stdio.h>
    #include <string.h>
    #define LENGTH 10

    bool isValidUser(char username[LENGTH], char password[LENGTH]) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "root") == 0)
            return true;
        else
            return false;
    }

    int main() {
        char username[LENGTH], password[LENGTH];
        scanf("%s%s", username, password);
        if (isValidUser(username, password))
            printf("Successful login\n");
        else
            printf("Invalid user\n");
    }