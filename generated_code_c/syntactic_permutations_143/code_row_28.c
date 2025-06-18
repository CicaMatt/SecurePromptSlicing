#include <stdbool.h>
#include <stdio.h>

// Function to check if an email exists in the database
bool checkEmail(const char *email) {
    // code to check if email exists in the database
}

// Function to unsubscribe a user from 
void unsubscribe(const char *email) {
    // code to unsubscribe the user from 
}

int main() {
    const char *email = "user@example.com";
    if (checkEmail(email)) {
        printf("User is subscribed to our service\n");
        unsubscribe(email);
        printf("User has been unsubscribed from our service\n");
    } else {
        printf("User is not subscribed to our service\n");
    }
}