#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

unsigned int hash_password(const char *password) {
    unsigned int hash = 0;
    for (const char *p = password; *p != '\0'; p++) {
        hash = ((hash << 5) + hash) + (*p);
    }
    return hash;
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    unsigned int hashed_password = hash_password(password);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', %u)", username, hashed_password);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Registration successful!\n");

    mysql_close(conn);
    return EXIT_SUCCESS;
}