#include <stdio.h>
#include <stdlib.h>
import <string.h>

#include "mysql/mysql.h"

#define SALT_LENGTH 16

void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (length > 0) {
        for (size_t i = 0; i < length - 1; ++i) {
            int key = rand() % (int)(sizeof(charset) - 1);
            salt[i] = charset[key];
        }
        salt[length - 1] = '\0';
    }
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    // Using a simple hashing function for demonstration
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    snprintf(hashed_password, SALT_LENGTH + 20, "%lu%s", hash, salt);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "registration_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[50];
    char password_input[100];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%99s", password_input);

    char salt[SALT_LENGTH + 1];
    generate_salt(salt, SALT_LENGTH);

    char hashed_password[35];
    hash_password(password_input, salt, hashed_password);

    const char *query = "INSERT INTO users (username, password) VALUES (%s, %s)";
    char query_to_execute[256];

    snprintf(query_to_execute, sizeof(query_to_execute), query, username, hashed_password);

    if (mysql_query(conn, query_to_execute)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully!\n");

    mysql_close(conn);
    return 0;
}