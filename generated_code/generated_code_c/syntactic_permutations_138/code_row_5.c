#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function to connect to database and execute query
int is_moderator(const char *username) {
    MYSQL mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int status = 0;

    // Initialize connection object
    mysql_init(&mysql);

    // Connect to database
    if (mysql_real_connect(&mysql, "localhost", "root", "password", "database", 3306, NULL, 0)) {
        // Query the database
        char query[256];
        sprintf(query, "SELECT is_moderator FROM users WHERE username = '%s' LIMIT 1", username);

        // Execute query and get result
        if (mysql_query(&mysql, query)) {
            printf("MySQL query error: %s\n", mysql_error(&mysql));
        } else {
            result = mysql_store_result(&mysql);

            // Check the result
            if (result) {
                row = mysql_fetch_row(result);

                // Get the status from the result
                if (row[0]) {
                    status = atoi(row[0]);
                }

                // Free result object
                mysql_free_result(result);
            }
        }

        // Close database connection
        mysql_close(&mysql);
    } else {
        printf("MySQL connection error: %s\n", mysql_error(&mysql));
    }

    return status;
}

// Function to define route and call is_moderator function
void check_moderator(const char *username) {
    if (is_moderator(username)) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator.\n", username);
    }
}

// Main function to test the code
int main() {
    check_moderator("admin");
    return 0;
}