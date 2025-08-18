#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "unsubscribe_db"

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE email = '%s'", email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);

    if (row) {
        printf("Unsubscribing email: %s\n", email);
        snprintf(query, sizeof(query), "DELETE FROM users WHERE email = '%s'", email);
        
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("Email unsubscribed successfully.\n");
        }
    } else {
        printf("Email not found in the database.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char email[256];

    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }

        unsubscribe(email);
    } else {
        fprintf(stderr, "Failed to read input.\n");
    }

    return 0;
}


**Note:** Make sure you have MySQL installed and properly configured on your system. Also, ensure the database and table (`unsubscribe_db` and `users`) exist with a column named `email`. Adjust connection parameters as needed.