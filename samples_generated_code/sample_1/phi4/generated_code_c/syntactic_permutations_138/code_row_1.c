#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function declarations
void handle_request(MYSQL *conn);
int is_moderator(const char *username, MYSQL *conn);

int main() {
    MYSQL *conn;

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return EXIT_FAILURE;
    }

    // Connect to the database
    if (mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }
    
    // Define route and handle request
    handle_request(conn);

    // Close MySQL connection
    mysql_close(conn);
    return 0;
}

void handle_request(MYSQL *conn) {
    char username[50];

    // Simulating a request with hardcoded username for demonstration
    strcpy(username, "test_user");

    int result = is_moderator(username, conn);
    if (result == 1) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator or does not exist.\n", username);
    }
}

int is_moderator(const char *username, MYSQL *conn) {
    char query[256];
    
    // Prepare SQL query
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s' AND is_moderator = 1", username);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1; // Error occurred
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0; // No result or error occurred
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    int is_moderator = (row && atoi(row[0]) > 0) ? 1 : 0;
    
    mysql_free_result(result);
    return is_moderator;
}


Make sure to replace `"localhost"`, `"root"`, `"password"`, and `"database_name"` with your actual MySQL server details.