#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

void unsubscribe(char *email) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "yourhost",
                            "username", "password",
                            "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    sprintf(query, "DELETE FROM subscribers WHERE email = '%s'", email);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("You have been unsubscribed.\n");
    }

    mysql_close(conn);
}

int main() {
    char email[256];
    printf("Enter your email address: ");
    scanf("%s", email);

    unsubscribe(email);
    return 0;
}