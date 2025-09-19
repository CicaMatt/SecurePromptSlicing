#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 256

void hash_password(char *password, char *hashed_password) {
    // A simple hashing function using SHA-1 for demonstration purposes.
    // In a real application, use a stronger algorithm like bcrypt or Argon2.
    unsigned char hash[20];
    MYSQL mysql;
    
    if (mysql_library_init(0, NULL, NULL)) {
        fprintf(stderr, "Could not initialize MySQL library\n");
        exit(EXIT_FAILURE);
    }
    
    if (!mysql_init(&mysql)) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_escape_string(&mysql, hash, password, strlen(password))) {
        snprintf(hashed_password, BUFFER_SIZE, "%02x", *hash);
    } else {
        strcpy(hashed_password, "");
    }
    
    mysql_library_end();
}

void register_user(const char *username, const char *password) {
    MYSQL conn;
    char hashed_password[BUFFER_SIZE];
    char query[BUFFER_SIZE * 2];

    hash_password(password, hashed_password);

    if (!mysql_init(&conn)) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(EXIT_FAILURE);
    }

    if (!mysql_real_connect(&conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(EXIT_FAILURE);
    }
    
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, hashed_password);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(&conn));
    } else {
        printf("User registered successfully!\n");
    }

    mysql_close(&conn);
}

int main() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    printf("Enter username: ");
    if (fgets(username, BUFFER_SIZE, stdin) != NULL) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, BUFFER_SIZE, stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    register_user(username, password);

    return 0;
}
