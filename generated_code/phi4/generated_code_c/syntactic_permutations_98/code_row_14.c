#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void register_user(MYSQL *conn, const char *username, const char *password);

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    register_user(conn, username, password);

    mysql_close(conn);
    return 0;
}

void register_user(MYSQL *conn, const char *username, const char *password) {
    char query[256];
    
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", 
             mysql_real_escape_string(conn, (char *)username), 
             mysql_real_escape_string(conn, (char *)password));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Registration successful!\n");
    }
}
