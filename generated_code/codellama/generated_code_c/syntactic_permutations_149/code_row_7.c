c
    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "database.h"
#define MAX_DATA 100
#define USERNAME_SIZE 50
#define MESSAGE_SIZE 200


int insert_user_message(char *username, char *message) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[MAX_DATA];

    /* Connect to database */
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    /* Insert message into database */
    sprintf(query,
            "INSERT INTO messages (username, message) VALUES ('%s', '%s')",
            username, message);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    /* Print messages from database */
    sprintf(query, "SELECT username, message FROM messages");
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }
    res = mysql_use_result(conn);
    printf("<html><body>");
    while ((row = mysql_fetch_row(res))) {
        printf("%s: %s<br>", row[0], row[1]);
    }
    printf("</body></html>");
    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char username[USERNAME_SIZE];
    char message[MESSAGE_SIZE];

    /* Get username and message from request */
    printf("Content-Type: text/plain\n");
    printf("\n");
    printf("<html><body>");
    printf("Please enter your name: ");
    fgets(username, USERNAME_SIZE, stdin);
    printf("Please enter message: ");
    fgets(message, MESSAGE_SIZE, stdin);

    /* Call function to insert message into database */
    if (insert_user_message(username, message)) {
        return EXIT_FAILURE;
    }

    /* Redirect user to / route */
    printf("</body></html>");
}