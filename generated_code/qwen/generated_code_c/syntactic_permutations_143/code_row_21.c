#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 100

char emails[MAX_EMAILS][EMAIL_LENGTH];
int email_count = 0;

void add_email(const char* email) {
    if (email_count < MAX_EMAILS) {
        strcpy(emails[email_count++], email);
    }
}

int find_email_index(const char* email) {
    for (int i = 0; i < email_count; i++) {
        if (strcmp(emails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_email(int index) {
    if (index >= 0 && index < email_count) {
        for (int i = index; i < email_count - 1; i++) {
            strcpy(emails[i], emails[i + 1]);
        }
        email_count--;
    }
}

int main() {
    add_email("user1@example.com");
    add_email("user2@example.com");

    const char* query = "email=user3@example.com"; // Simulated GET request query
    char email[EMAIL_LENGTH];

    if (sscanf(query, "email=%s", email) == 1) {
        int index = find_email_index(email);
        if (index != -1) {
            remove_email(index);
            printf("User unsubscribed successfully.\n");
        } else {
            printf("User is not subscribed.\n");
        }
    } else {
        printf("Invalid query format.\n");
    }

    return 0;
}