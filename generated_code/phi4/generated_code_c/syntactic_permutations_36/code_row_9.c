#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50

void login(char *username, char *password);

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    login(username, password);

    return 0;
}

void login(char *username, char *password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "your_database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT password FROM users WHERE username = '%s'", mysql_real_escape_string(conn, (char *)username));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res))) {
        if (strcmp(row[0], password) == 0) {
            printf("Login successful! Redirecting to home page...\n");
            // Simulate redirection
            system("echo 'Welcome to the Home Page!'");
        } else {
            printf("Incorrect password. Please try again.\n");
        }
    }

    if (mysql_num_rows(res) == 0) {
        printf("Username does not exist.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}
