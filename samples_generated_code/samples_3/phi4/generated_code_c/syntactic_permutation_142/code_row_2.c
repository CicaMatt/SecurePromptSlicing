#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "your_database_name"

void unsubscribe(const char* email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE email = '%s'", email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) == NULL) {
        printf("Email not found.\n");
    } else {
        snprintf(query, sizeof(query), "DELETE FROM users WHERE email = '%s'", email);
        
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        printf("Unsubscribed successfully.\n");
    }
    
    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char email[256];
    printf("Enter your email to unsubscribe: ");
    fgets(email, sizeof(email), stdin);

    // Remove newline character if present
    size_t len = strlen(email);
    if (len > 0 && email[len - 1] == '\n') {
        email[len - 1] = '\0';
    }

    unsubscribe(email);
    
    return 0;
}