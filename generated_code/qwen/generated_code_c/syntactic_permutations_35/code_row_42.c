#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int check_login(const char* username, const char* password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username='%s' AND password='%s'", username, password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    int exists = (mysql_num_rows(res) > 0);

    mysql_free_result(res);
    mysql_close(conn);

    return exists;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <username> <password>\n", argv[0]);
        return 1;
    }

    const char* username = argv[1];
    const char* password = argv[2];

    if (check_login(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would use HTTP headers for redirection
        // printf("Location: /home.html\n\n");
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // In a real web application, you would use HTTP headers for redirection
        // printf("Location: /login.html\n\n");
    }

    return 0;
}