#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void unsubscribe(const char* email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        char query[256];
        snprintf(query, sizeof(query), "SELECT email FROM subscribers WHERE email='%s'", email);
        
        if (mysql_query(conn, query) == 0) {
            res = mysql_store_result(conn);

            if ((row = mysql_fetch_row(res))) {
                snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email='%s'", email);
                if (mysql_query(conn, query) == 0) {
                    printf("You have been unsubscribed successfully.\n");
                } else {
                    printf("Error removing your email from the database: %s\n", mysql_error(conn));
                }
            } else {
                printf("Your email address is not in our database.\n");
            }

            mysql_free_result(res);
        } else {
            printf("Failed to execute query: %s\n", mysql_error(conn));
        }

        mysql_close(conn);
    } else {
        fprintf(stderr, "Error connecting to the database: %s\n", mysql_error(conn));
    }
}

int main() {
    char email[256];
    
    printf("Please enter your email address to unsubscribe:\n");
    if (fgets(email, sizeof(email), stdin)) {
        // Remove newline character from input
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
        unsubscribe(email);
    } else {
        printf("Failed to read email address.\n");
    }

    return 0;
}