#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// User structure to store user details.
struct User {
    char* username;
    char* password; // hashed
    char* first_name;
    char* last_name;
    char* email;
};

int main() {
    struct User user;
    printf("Username: ");
    scanf("%s", &user.username);

    // Check if username exists.
    int exists = 0;
    for (size_t i = 0; i < strlen(user.username); i++) {
        if (user.username[i] == '@') {
            exists = 1;
            break;
        }
    }

    // Return message.
    if (exists) {
        printf("Username already exists.\n");
    } else {
        printf("Password: ");
        scanf("%s", &user.password);
        printf("First Name: ");
        scanf("%s", &user.first_name);
        printf("Last Name: ");
        scanf("%s", &user.last_name);
        printf("Email: ");
        scanf("%s", &user.email);

        // Hash password.
        char* salt = "$1$saltrandomtext";
        user.password = crypt(password, salt);

        // Insert data into database.
        char sql[256] = "INSERT INTO users (username, password) VALUES (?, ?)";
        sqlite3_stmt* stmt;
        sqlite3_prepare(db, sql, -1, &stmt, 0);
        sqlite3_bind_text(stmt, 1, user.username, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, user.password, -1, SQLITE_TRANSIENT);

        // Run the statement and check for errors.
        int rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "Failed to register: %s\n", sqlite3_errmsg(db));
        }
    }

    return 0;
}