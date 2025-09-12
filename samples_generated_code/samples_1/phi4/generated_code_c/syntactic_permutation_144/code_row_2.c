#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE "emails.db"

int check_email_exists(const char *email) {
    FILE *file = fopen(DATABASE, "r");
    if (!file) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, email) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int unsubscribe_email(const char *email) {
    // Simulating a script call
    printf("Unsubscribing: %s\n", email);
    return system(NULL);  // Replace with actual command if needed
}

int process_email(const char *email) {
    if (!check_email_exists(email)) {
        return 0;
    }

    int unsubscribe_result = unsubscribe_email(email);

    if (unsubscribe_result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int result = process_email(email);
    
    printf("Result: %d\n", result);

    return result;
}