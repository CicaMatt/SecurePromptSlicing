#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <crypt.h>

#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char hash[MAX_LEN * 2]; // Hash can be longer than original password
} User;

int user_exists(const char *username) {
    FILE *db = fopen("users.db", "r");
    if (db == NULL) return 0;

    User u;
    while (fscanf(db, "%s %s", u.username, u.hash) != EOF) {
        if (strcmp(u.username, username) == 0) {
            fclose(db);
            return 1;
        }
    }

    fclose(db);
    return 0;
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    char salt[128];
    strcpy(salt, crypt(password, "sa")); // Using a simple salt for demonstration
    char hashed_password[MAX_LEN * 2];
    strcpy(hashed_password, crypt(password, salt));

    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        printf("Failed to open database file.\n");
        return;
    }

    fprintf(db, "%s %s\n", username, hashed_password);
    fclose(db);

    printf("Registration succeeded.\n");

    // Optionally, you can store first_name, last_name, and email in a separate file or database table
}

int main() {
    char username[MAX_LEN], password[MAX_LEN], first_name[MAX_LEN], last_name[MAX_LEN], email[MAX_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter email: ");
    scanf("%s", email);

    register_user(username, password, first_name, last_name, email);

    return 0;
}