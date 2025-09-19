#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50

void login(const char *username, const char *password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    // Connect to the database
    if (mysql_real_connect(conn, "localhost", "root", "", "your_database_name", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char query[256];
    sprintf(query, "SELECT password FROM users WHERE username = '%s'", username);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    // Check if the user exists and verify the password
    if ((row = mysql_fetch_row(res))) {
        if (strcmp(row[0], password) == 0) {
            printf("Login successful. Redirecting to home page...\n");
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Username not found.\n");
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}
