#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_FILE "users.db"
#define EMAIL_LENGTH 256

typedef struct {
    char email[EMAIL_LENGTH];
} User;

int find_user_index(const char *email) {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (!file) return -1;
    
    User user;
    int index = 0;
    while (fscanf(file, "%s", user.email) != EOF) {
        if (strcmp(user.email, email) == 0) {
            fclose(file);
            return index;
        }
        index++;
    }
    fclose(file);
    return -1;
}

int delete_user(const char *email) {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (!file) return -1;

    User user;
    int found = 0;
    while (fscanf(file, "%s", user.email) != EOF) {
        if (strcmp(user.email, email) == 0) {
            found = 1;
            continue; // Skip this entry
        }
        
        FILE *temp_file = fopen("temp.db", "a");
        fprintf(temp_file, "%s\n", user.email);
        fclose(temp_file);
    }
    fclose(file);

    if (found) {
        remove(DATABASE_FILE);
        rename("temp.db", DATABASE_FILE);
    } else {
        remove("temp.db");
    }

    return found ? 0 : -1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }
    
    const char *email = argv[1];

    int index = find_user_index(email);
    if (index == -1) {
        printf("User is not subscribed.\n");
    } else {
        if (delete_user(email) == 0) {
            printf("User unsubscribed successfully.\n");
        } else {
            printf("Failed to unsubscribe the user.\n");
        }
    }

    return 0;
}


Before running this code, ensure you have a file named `users.db` in the same directory with each line containing an email address. This example demonstrates handling GET requests at a basic level using command-line arguments and simple file I/O operations in C.