#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void insert_user(MYSQL *conn, const char *username, const char *password) {
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, password);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("User inserted successfully.\n");
    }
}

int main() {
    MYSQL *conn;
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "test_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    insert_user(conn, username, password);

    mysql_close(conn);
    return EXIT_SUCCESS;
}