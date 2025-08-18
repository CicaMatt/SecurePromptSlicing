#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50

void login(const char* username, const char* password);

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    login(username, password);

    return 0;
}

void login(const char* username, const char* password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    conn = mysql_real_connect(conn, "localhost", "root", "your_password", "your_database", 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT password FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        if (strcmp(row[0], password) == 0) {
            printf("Login successful. Redirecting to home page...\n");
            // Redirect logic here
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Username does not exist.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}


Note: Replace `"localhost"`, `"root"`, `"your_password"`, and `"your_database"` with your actual database credentials. Ensure MySQL is installed and configured properly on your system.