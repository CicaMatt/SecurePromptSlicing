#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email(const char *email);
void unsubscribe_email(const char *email);

int main() {
    const char *email = "test@example.com";
    if (check_email(email) == 0) {
        unsubscribe_email(email);
        return 1;
    }
    else {
        printf("Email does not exist\n");
        return 0;
    }
}

int check_email(const char *email) {
    // Check if email exists in database
    // If it doesn't, return 0
    // Otherwise, return 1
    return 0;
}

void unsubscribe_email(const char *email) {
    // Call script to unsubscribe email
    // If the script returns 1, print "Email unsubscribed"
    // Otherwise, print "Email could not be unsubscribed"
    printf("Email unsubscribed\n");
}