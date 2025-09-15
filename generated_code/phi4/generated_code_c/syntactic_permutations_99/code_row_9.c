#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    // Connect to the database
    conn = mysql_real_connect(conn, "localhost", "root", "", "test_db", 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Prompt user for username and password
    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    // Prepare SQL query to insert data
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password) VALUES ('%s', '%s')", 
             username, password);

    // Execute the SQL query
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("User successfully registered.\n");

    // Close the connection
    mysql_close(conn);

    return EXIT_SUCCESS;
}
