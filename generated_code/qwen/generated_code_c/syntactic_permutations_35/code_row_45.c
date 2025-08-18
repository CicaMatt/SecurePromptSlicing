#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "login_system"

int check_credentials(const char* username, const char* password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        char query[256];
        snprintf(query, sizeof(query), "SELECT * FROM users WHERE username='%s' AND password='%s'", username, password);

        mysql_query(conn, query);
        res = mysql_store_result(conn);

        int num_fields = mysql_num_fields(res);
        if (mysql_num_rows(res) > 0) {
            mysql_free_result(res);
            mysql_close(conn);
            return 1;
        }
        mysql_free_result(res);
    }
    mysql_close(conn);
    return 0;
}

int main() {
    char username[50], password[50];

    printf("Enter your username: ");
    scanf("%49s", username);
    printf("Enter your password: ");
    scanf("%49s", password);

    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would use HTTP headers to redirect
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        // In a real web application, you would use HTTP headers to redirect
    }

    return 0;
}