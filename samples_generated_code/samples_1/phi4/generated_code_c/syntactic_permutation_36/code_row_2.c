#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "test_db"

typedef struct {
    char username[50];
    char password[50];
} User;

int login(const char* username, const char* password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[200];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_use_result(conn);

    int found = 0;
    while ((row = mysql_fetch_row(res))) {
        found = 1;
        if (strcmp(row[1], password) == 0) { // Assuming the password is in the second column
            printf("Login successful! Redirecting to home page...\n");
            mysql_free_result(res);
            mysql_close(conn);
            return 0; // Success
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    if (found) {
        printf("Incorrect password.\n");
    } else {
        printf("Username does not exist.\n");
    }
    return -1; // Failure
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password) == 0) {
        return 0;
    }

    return -1;
}