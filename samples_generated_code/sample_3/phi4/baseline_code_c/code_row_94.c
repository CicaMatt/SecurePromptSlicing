#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_SIZE 33

void hash_password(const char *password, char *hashed) {
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    sprintf(hashed, "%lx", hash);
}

int connect_to_database(MYSQL **conn) {
    *conn = mysql_init(NULL);

    if (*conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(*conn, "localhost", "root", "", "test_db", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(*conn));
        return 1;
    }
    
    return 0;
}

int register_user(const char *username, const char *password) {
    MYSQL *conn;
    char hashed_password[HASH_SIZE];
    char query[256];

    hash_password(password, hashed_password);

    if (connect_to_database(&conn)) {
        mysql_close(conn);
        return 1;
    }

    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", 
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    mysql_close(conn);
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    if (scanf("%49s", username) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Enter password: ");
    if (scanf("%49s", password) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (register_user(username, password)) {
        fprintf(stderr, "Registration failed\n");
        return 1;
    }

    printf("User registered successfully!\n");

    return 0;
}