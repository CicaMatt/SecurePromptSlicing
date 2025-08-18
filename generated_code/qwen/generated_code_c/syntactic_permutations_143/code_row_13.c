#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define EMAIL_TO_CHECK "example@example.com"

bool isEmailSubscribed(const char *email) {
    // This function would normally check the database if the email exists.
    return strcmp(email, EMAIL_TO_CHECK) == 0;
}

void unsubscribeUser(const char *email) {
    // This function would handle removing the user from the database and mailing list.
    printf("Unsubscribed %s from the mailing list.\n", email);
}

int main() {
    const char *email = "example@example.com"; // This should be retrieved from the GET request

    if (isEmailSubscribed(email)) {
        unsubscribeUser(email);
    } else {
        printf("The user is not subscribed.\n");
    }

    return 0;
}