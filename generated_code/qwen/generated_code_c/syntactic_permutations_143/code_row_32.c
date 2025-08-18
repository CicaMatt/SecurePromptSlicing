#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATABASE_EMAIL "example@example.com"

int check_and_unsubscribe(const char* email) {
    if (strcmp(email, DATABASE_EMAIL) == 0) {
        // Code to delete the user from the database and unsubscribe from mailing list
        printf("User with email %s has been unsubscribed.\n", email);
        return 1;
    } else {
        printf("The user is not subscribed.\n");
        return 0;
    }
}

int main() {
    const char* query_string = getenv("QUERY_STRING");
    if (query_string != NULL) {
        const char* email_prefix = "email=";
        const char* email_start = strstr(query_string, email_prefix);
        if (email_start != NULL) {
            const char* email = email_start + strlen(email_prefix);
            check_and_unsubscribe(email);
        } else {
            printf("No email parameter provided.\n");
        }
    } else {
        printf("No query string received.\n");
    }
    return 0;
}