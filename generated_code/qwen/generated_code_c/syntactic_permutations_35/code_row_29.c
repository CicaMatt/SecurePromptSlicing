#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "userdb"

int check_credentials(const char *username, const char *password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username='%s' AND password='%s'", username, password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int exists = 0;
    if ((row = mysql_fetch_row(res))) {
        exists = 1;
    }

    mysql_free_result(res);
    mysql_close(conn);

    return exists;
}

int main() {
    const char *username = "testuser"; // This should be obtained from form data
    const char *password = "testpass"; // This should be obtained from form data

    if (check_credentials(username, password)) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome to the Home Page</h1>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Username or password is incorrect. Please try again.</p>");
        printf("<a href='login.html'>Go back to login page</a>");
        printf("</body></html>");
    }

    return 0;
}