#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_database_functions.h" // You can include your own database functions here

int login(char *username, char *password) {
    // Query the database to check if username exists
    char query[1024];
    sprintf(query, "SELECT password FROM user_table WHERE username = '%s'", username);
    char *db_password = database_query(query);

    // If username does not exist return 0
    if (strlen(db_password) == 0) {
        return 0;
    }

    // Check if password is correct
    if (strcmp(password, db_password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    // Call login function with the user-entered values
    int result = login(username, password);

    if (result == 1) {
        printf("Login successful. Redirecting to home page...");
    } else {
        printf("Invalid username or password.");
    }

    return 0;
}