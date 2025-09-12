#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "testdb"

unsigned long hash_password(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
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
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username = '%s'", username);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Username already exists.\n");
    } else {
        snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', %lu, '%s', '%s', '%s')", username, hashed_password, first_name, last_name, email);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("Registration succeeded.\n");
        }
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char username[50], password[50], first_name[50], last_name[50], email[100];

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    register_user(username, password, first_name, last_name, email);

    return 0;
}