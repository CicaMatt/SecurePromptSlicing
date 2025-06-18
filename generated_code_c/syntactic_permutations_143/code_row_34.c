#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    char email[50];
    int is_subscribed = 1;

    // Get email from user input
    printf("Enter your email: ");
    fgets(email, sizeof(email), stdin);
    size_t len = strlen(email);
    if (email[len-1] == '\n') {
        email[len-1] = '\0'; // replace newline with null byte
    } else {
        printf("Error: Email too long\n");
        return 1;
    }

    // Connect to database
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Error: Could not create SQL connection object.\n");
        return 1;
    }
    conn = mysql_real_connect(conn, "localhost", "yourusername", "yourpassword", "database_name", 0, NULL, 0);
    if (conn == NULL) {
        printf("Error: Could not connect to SQL database.\n");
        return 1;
    }

    // Check if email exists in database
    char sql[256];
    sprintf(sql, "SELECT COUNT(*) FROM users WHERE email = '%s'", email);
    MYSQL_RES *result = mysql_query(conn, sql);
    int num_rows = mysql_num_rows(result);
    if (num_rows == 0) {
        is_subscribed = 0;
    }
    mysql_free_result(result);

    // Delete email from database and unsubscribe from mailing list
    if (is_subscribed == 1) {
        sprintf(sql, "DELETE FROM users WHERE email = '%s'", email);
        result = mysql_query(conn, sql);
        num_rows = mysql_num_rows(result);
        if (num_rows > 0) {
            printf("Unsubscribed successfully.\n");
        } else {
            printf("Error: Could not unsubscribe from mailing list.\n");
        }
    }

    // Close database connection
    mysql_close(conn);

    return 0;
}