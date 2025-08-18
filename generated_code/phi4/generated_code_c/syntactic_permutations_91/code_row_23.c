#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "user_db"

unsigned long hash_password(const char *password) {
    unsigned long hashed = 5381;
    int c;

    while ((c = *password++))
        hashed = ((hashed << 5) + hashed) + c; /* hash * 33 + c */

    return hashed;
}

void register_user(const char *username, const char *password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    unsigned long hashed_password = hash_password(password);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', %lu)", username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    register_user(username, password);

    return 0;
}


Note: Before running this code:
1. Ensure you have MySQL installed and configured on your system.
2. Create a database named `user_db` and a table `users` with columns `username` (VARCHAR) and `password` (UNSIGNED LONG).
3. Link against the MySQL client library using `-lmysqlclient` when compiling, e.g., `gcc -o register_app app.c -lmysqlclient`.