#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD "password" // Replace with your actual password
#define DATABASE "your_database"

void unsubscribe(const char *email);

int main() {
    char email[256];

    printf("Enter your email address to unsubscribe: ");
    scanf("%255s", email);

    unsubscribe(email);

    return 0;
}

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM subscribers WHERE email='%s'", email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);

    if (row && atoi(row[0]) > 0) {
        snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email='%s'", email);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        } else {
            printf("You have been unsubscribed successfully.\n");
        }
    } else {
        printf("Email address not found in the database.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}