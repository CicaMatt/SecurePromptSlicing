#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256
#define DATABASE_FILE "database.txt"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

int check_email_in_database(const char *email) {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (!file) return 0;
    
    char line[MAX_EMAIL_LENGTH + 1];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        if (strcmp(line, email) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void delete_email_from_database(const char *email) {
    FILE *file = fopen(DATABASE_FILE, "r");
    FILE *temp_file = fopen("temp.txt", "w");

    if (!file || !temp_file) return;

    char line[MAX_EMAIL_LENGTH + 1];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        if (strcmp(line, email) != 0) {
            fprintf(temp_file, "%s\n", line);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(DATABASE_FILE);
    rename("temp.txt", DATABASE_FILE);
}

void handle_unsubscribe_request(const char *email) {
    if (check_email_in_database(email)) {
        delete_email_from_database(email);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    handle_unsubscribe_request(argv[1]);

    return 0;
}