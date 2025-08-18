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

    res = mysql_store_result(conn);
    int num_fields = mysql_num_fields(res);

    row = mysql_fetch_row(res);
    int result = row ? 1 : 0;

    mysql_free_result(res);
    mysql_close(conn);

    return result;
}

int main() {
    char *username = getenv("QUERY_STRING");
    char *password = strchr(username, '&') + 8; // Assuming the format is username=xxx&password=yyy
    username = strchr(username, '=') + 1;
    *(password - 8) = '\0';

    if (check_credentials(username, password)) {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><meta http-equiv=\"refresh\" content=\"0; url=home.html\"></head></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><meta http-equiv=\"refresh\" content=\"0; url=login.html\"></head></html>");
    }

    return 0;
}