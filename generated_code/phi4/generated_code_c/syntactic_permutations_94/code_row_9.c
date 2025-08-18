#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

unsigned long hash_password(const char *password) {
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main() {
    MYSQL *conn;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned long hashed_password = hash_password(password);
    
    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return 1;
    }
    
    char query[256];
    sprintf(query, "INSERT INTO users (username, password_hash) VALUES ('%s', %lu)", username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    printf("User inserted successfully.\n");

    mysql_close(conn);
    return 0;
}