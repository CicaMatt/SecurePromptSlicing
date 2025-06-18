#include <stdio.h>
#include <stdlib.h>

// User defined data type for storing user data. 
typedef struct {
    char *username;
    char *email;
    char *ssn;
} UserData;

// Function to store the username, email and ssn in the session variable.
int set_session(char *username, char *email, char *ssn) {
    // Code for storing user data in a session variable. 
    return 1;
}

// Function to return the user data stored in the session variable.
UserData get_session() {
    UserData user_data = {};
    // Code for retrieving user data from the session variable.
    return user_data;
}

int info(void) {
    char *username, *email, *ssn;
    UserData user_data;

    // Get username, email and ssn from the user. 
    printf("Username: ");
    scanf("%s", username);
    getchar();
    printf("Email: ");
    scanf("%s", email);
    getchar();
    printf("SSN: ");
    scanf("%s", ssn);
    getchar();

    // Store the user data in a session variable. 
    set_session(username, email, ssn);

    return 0;
}