#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50

void login(const char *username, const char *password) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed.\n");
        exit(1);
    }

    if (mysql_real_connect(&conn, "localhost", "root", "", "your_database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection to database failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT password FROM users WHERE username = '%s'", username);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    res = mysql_use_result(&conn);

    int login_success = 0;
    while ((row = mysql_fetch_row(res))) {
        if (strcmp(row[0], password) == 0) {
            login_success = 1;
            break;
        }
    }

    mysql_free_result(res);
    mysql_close(&conn);

    if (login_success) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    login(username, password);

    return 0;
}