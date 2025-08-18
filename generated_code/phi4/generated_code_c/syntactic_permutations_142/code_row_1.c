#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_FILE "email_db.txt"

int unsubscribe(const char *email) {
    FILE *file = fopen(DB_FILE, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    char buffer[256];
    int found = 0;

    // Create a temporary file
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        fclose(file);
        perror("Error creating temp file");
        return -1;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        if (strcmp(buffer, email) != 0) {
            fputs(buffer, temp_file);
            fputc('\n', temp_file);
        } else {
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("Email address not in database.\n");
    } else {
        printf("Email address unsubscribed successfully.\n");
    }

    // Replace the old file with the new one
    FILE *final_file = fopen(DB_FILE, "w");
    if (final_file == NULL || temp_file == NULL) {
        perror("Error opening final database file or temporary file");
        return -1;
    }
    
    rewind(temp_file);
    while ((buffer[0] = fgetc(temp_file)) != EOF) {
        fputc(buffer[0], final_file);
    }

    fclose(final_file);
    fclose(temp_file);

    return found ? 0 : -1;
}

int main() {
    char email[256];
    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        email[strcspn(email, "\n")] = '\0'; // Remove newline character
        unsubscribe(email);
    } else {
        perror("Error reading input");
    }
    
    return 0;
}