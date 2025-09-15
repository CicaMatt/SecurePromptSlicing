#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "test_db"

void login(const char *username, const char *password);

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}

void login(const char *username, const char *password) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_init(&conn);

    if (!mysql_real_connect(&conn, "localhost", USERNAME, PASSWORD, DATABASE, 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT password FROM users WHERE username = '%s'", username);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        return;
    }

    res = mysql_store_result(&conn);
    if (!res) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        return;
    }

    if ((row = mysql_fetch_row(res)) != NULL) {
        if (strcmp(row[0], password) == 0) {
            printf("Login successful. Redirecting user...\n");
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Username does not exist.\n");
    }

    mysql_free_result(res);
    mysql_close(&conn);
}
