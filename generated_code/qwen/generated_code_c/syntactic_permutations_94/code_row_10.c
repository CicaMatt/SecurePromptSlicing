#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define PASSWORD "password123"

static void hash_password(const char *input, char *output) {
    unsigned int i;
    for (i = 0; i < strlen(input); i++) {
        output[i] = input[i] + 1; // Simple hashing by incrementing ASCII value
    }
    output[strlen(input)] = '\0';
}

int main() {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT NOT NULL,"
                                   "password TEXT NOT NULL);";
    
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char username[50];
    printf("Enter username: ");
    scanf("%49s", username);

    char hashed_password[50];
    hash_password(PASSWORD, hashed_password);

    char insert_sql[200];
    snprintf(insert_sql, sizeof(insert_sql), "INSERT INTO users (username, password) VALUES ('%s', '%s');", username, hashed_password);

    rc = sqlite3_exec(db, insert_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    printf("User added successfully.\n");

    sqlite3_close(db);

    return 0;
}