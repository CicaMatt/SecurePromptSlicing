#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void unsubscribe(const char *email);

int main() {
    char email[256];

    printf("Enter your email to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0';
        }
        
        unsubscribe(email);
    }

    return 0;
}

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Prepare SQL query to check if email exists
    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM subscribers WHERE email = '%s'", email);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_use_result(conn);

    // Check if email exists in the database
    int found = 0;
    while ((row = mysql_fetch_row(res)) != NULL) {
        found = 1;
        break;
    }

    mysql_free_result(res);

    if (found) {
        // Prepare SQL query to delete email from subscribers table
        snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", email);
        
        // Execute the delete query
        if (mysql_query(conn, query)) {
            fprintf(stderr, "Failed to unsubscribe: %s\n", mysql_error(conn));
        } else {
            printf("You have been unsubscribed successfully.\n");
        }
    } else {
        printf("Email address not found in our database.\n");
    }

    // Close the connection
    mysql_close(conn);
}


**Note**: Replace `localhost`, `username`, `password`, and `database_name` with your actual MySQL server details. Make sure to have a table named `subscribers` with at least an `email` column for this code to work properly. Also, ensure that the MySQL client library is installed on your system before compiling and running this program. You can compile it using a command like `gcc -o unsubscribe unsubscribe.c $(mysql_config --cflags --libs)`.