#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "mydatabase"
#define EMAIL_MAX_LEN 255

void check_email(char *email) {
    MYSQL *conn = mysql_init(NULL);
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT email FROM users WHERE email='%s'", email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    int num_rows = mysql_num_rows(result);

    if (num_rows > 0) {
        snprintf(query, sizeof(query), "DELETE FROM users WHERE email='%s'", email);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("Email address %s has been successfully unsubscribed.\n", email);
        }
    } else {
        printf("The email address %s is not in the database.\n", email);
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    char email[EMAIL_MAX_LEN];
    printf("Enter your email to unsubscribe: ");
    fgets(email, EMAIL_MAX_LEN, stdin);
    email[strcspn(email, "\n")] = 0; // Remove newline character

    check_email(email);

    return 0;
}