#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "your_username"; // Change to your MySQL username
    const char *password = "your_password"; // Change to your MySQL password
    const char *database = "your_database_name"; // Change to your database name

    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM subscribers WHERE email = '%s'", email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    row = mysql_fetch_row(res);
    int count = atoi(row[0]);
    mysql_free_result(res);

    if (count > 0) {
        snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", email);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("Email address unsubscribed successfully.\n");
        }
    } else {
        printf("Email address not found in the database.\n");
    }

    mysql_close(conn);
}

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
    }

    return 0;
}
