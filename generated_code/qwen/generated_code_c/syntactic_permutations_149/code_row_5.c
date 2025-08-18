#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void insert_user_message_in_db(const char *username, const char *message) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO messages (username, message) VALUES ('%s', '%s')", username, message);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

void display_messages() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, "SELECT username, message FROM messages")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    printf("Content-type: text/html\n\n");
    printf("<html><body>");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("<p><strong>%s:</strong> %s</p>", row[0], row[1]);
    }
    printf("</body></html>");

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    if (strcmp(method, "POST") == 0) {
        char username[256];
        char message[256];

        // Simulating reading POST data for demonstration purposes
        scanf("username=%[^&]&message=%s", username, message);

        insert_user_message_in_db(username, message);
    }

    printf("Location: /\r\n\r\n");
    display_messages();

    return 0;
}