#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void connect_db();
void disconnect_db();
int email_exists(char *email);
void unsubscribe_user(char *email);

int main() {
    char email[100];
    printf("Enter your email: ");
    scanf("%s", email);
    if (email_exists(email)) {
        unsubscribe_user(email);
        printf("You have been successfully unsubscribed!\n");
    } else {
        printf("You are not subscribed to our mailing list.\n");
    }
}

void connect_db() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "users", 0, NULL, 0)) {
        printf("Error: %s\n", mysql_error(conn));
        exit(1);
    }
}

void disconnect_db() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "users", 0, NULL, 0)) {
        printf("Error: %s\n", mysql_error(conn));
        exit(1);
    } else {
        mysql_close(conn);
    }
}

int email_exists(char *email) {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "users", 0, NULL, 0)) {
        printf("Error: %s\n", mysql_error(conn));
        exit(1);
    } else {
        char sql[256];
        sprintf(sql, "SELECT * FROM users WHERE email = '%s'", email);
        MYSQL_RES *result;
        MYSQL_ROW row;
        if (mysql_query(conn, sql)) {
            printf("Error: %s\n", mysql_error(conn));
            exit(1);
        } else {
            result = mysql_store_result(conn);
            row = mysql_fetch_row(result);
            if (strcmp(email, row[0]) == 0) {
                return 1;
            }
        }
    }
}

void unsubscribe_user(char *email) {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "users", 0, NULL, 0)) {
        printf("Error: %s\n", mysql_error(conn));
        exit(1);
    } else {
        char sql[256];
        sprintf(sql, "DELETE FROM users WHERE email = '%s'", email);
        if (mysql_query(conn, sql)) {
            printf("Error: %s\n", mysql_error(conn));
            exit(1);
        } else {
            puts("User has been successfully deleted!\n");
        }
    }
}