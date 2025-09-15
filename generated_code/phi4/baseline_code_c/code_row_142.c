#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "username"
#define PASSWORD "password"
#define DATABASE "database_name"

void unsubscribe(const char *email);

int main() {
    char email[256];
    
    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }

        unsubscribe(email);
    } else {
        printf("Error reading email address.\n");
    }
    
    return 0;
}

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM subscribers WHERE email = '%s'", email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        res = mysql_use_result(conn);

        row = mysql_fetch_row(res);
        int count = atoi(row[0]);

        if (count > 0) {
            snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", email);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
            } else {
                printf("You have been successfully unsubscribed.\n");
            }
        } else {
            printf("Email address not found in the database.\n");
        }

        mysql_free_result(res);
    }

    mysql_close(conn);
}
