#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "test_db"

int check_credentials(const char* username, const char* password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username='%s' AND password='%s'", username, password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int found = (mysql_fetch_row(res) != NULL);

    mysql_free_result(res);
    mysql_close(conn);

    return found;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <username> <password>\n", argv[0]);
        return 1;
    }

    const char* username = argv[1];
    const char* password = argv[2];

    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would use HTTP headers to redirect
        // printf("Location: /home\n");
        // printf("\n");
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
        // In a real web application, you would use HTTP headers to redirect
        // printf("Location: /login\n");
        // printf("\n");
    }

    return 0;
}