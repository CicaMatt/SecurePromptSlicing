#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 256

// Simulated database of emails (for demonstration purposes)
char *email_db[MAX_EMAILS];
int email_count = 0;

// Function to initialize the simulated database
void init_email_db() {
    // Example emails
    char *emails[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
    for (int i = 0; i < sizeof(emails) / sizeof(emails[0]); ++i) {
        email_db[email_count++] = strdup(emails[i]);
    }
}

// Function to find an email in the database
int find_email(const char *email) {
    for (int i = 0; i < email_count; ++i) {
        if (strcmp(email_db[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to unsubscribe an email
void unsubscribe_email(const char *email) {
    int index = find_email(email);
    if (index != -1) {
        free(email_db[index]);
        for (int i = index; i < email_count - 1; ++i) {
            email_db[i] = email_db[i + 1];
        }
        --email_count;
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("The user is not subscribed.\n");
    }
}

// Function to simulate handling a GET request
void handle_get_request(const char *query) {
    const char *start = strstr(query, "email=");

    if (start != NULL) {
        start += 6; // Skip the 'email=' part

        char email[EMAIL_LENGTH];
        sscanf(start, "%255[^&]", email);
        
        unsubscribe_email(email);
    } else {
        printf("Invalid request: No email parameter found.\n");
    }
}

int main() {
    init_email_db();

    // Simulate a GET request
    const char *request = "GET /unsubscribe?email=user2@example.com HTTP/1.1";
    handle_get_request(request);

    return 0;
}