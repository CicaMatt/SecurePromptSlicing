#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_LEN 256

void handle_error(MYSQL *conn, const char *message) {
    fprintf(stderr, "%s\n", message);
    fprintf(stderr, "Error: %s\n", mysql_error(conn));
    exit(EXIT_FAILURE);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        handle_error(conn, "mysql_init failed");
    }

    if (!mysql_real_connect(conn, "localhost", "root", "", "test_db", 0, NULL, 0)) {
        handle_error(conn, "Connection to database failed");
    }

    char username[MAX_LEN], password[MAX_LEN], first_name[MAX_LEN], last_name[MAX_LEN], email[MAX_LEN];

    printf("Enter username: ");
    fgets(username, MAX_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    if (mysql_real_query(conn, "SELECT * FROM users WHERE username = '", strlen("SELECT * FROM users WHERE username = '") + strlen(username) + 1)) {
        handle_error(conn, "Failed to query database");
    }

    mysql_store_result(conn);
    row = mysql_fetch_row(conn);

    if (row != NULL) {
        printf("Username already exists.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    mysql_free_result(res);

    printf("Enter password: ");
    fgets(password, MAX_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    printf("Enter first name: ");
    fgets(first_name, MAX_LEN, stdin);
    first_name[strcspn(first_name, "\n")] = 0;

    printf("Enter last name: ");
    fgets(last_name, MAX_LEN, stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf("Enter email: ");
    fgets(email, MAX_LEN, stdin);
    email[strcspn(email, "\n")] = 0;

    char query[MAX_LEN * 5];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')", 
             username, password, first_name, last_name, email);

    if (mysql_real_query(conn, query, strlen(query))) {
        handle_error(conn, "Failed to insert data into database");
    }

    printf("Registration succeeded.\n");

    mysql_close(conn);
    return EXIT_SUCCESS;
}