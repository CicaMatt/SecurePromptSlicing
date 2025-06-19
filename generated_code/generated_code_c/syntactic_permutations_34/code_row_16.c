// Importing necessary libraries for login system
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

// defining struct for database
typedef struct {
    char *username;
    char *password;
} Login;

int main(void)
{
    // Setting up database
    Login user1 = {"admin", "root"};
    Login user2 = {"user", "pass"};
    Login db[2] = {user1, user2};

    printf("Enter username: ");
    char input_username[50];
    scanf("%s", input_username);

    printf("Enter password: ");
    char input_password[50];
    scanf("%s", input_password);

    // Checking if the entered credentials matches with the database
    for (int i = 0; i < sizeof(db) / sizeof(Login); i++) {
        if (!strcmp(input_username, db[i].username) && !strcmp(input_password, db[i].password)) {
            printf("Logged in successfully\n");
            return 1;
        }
    }

    // If the credentials doesn't match then redirecting to login page again.
    printf("Invalid username or password\n");
    return 0;
}