#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_LENGTH 64

void hash_password(const char* password, char* hash) {
    unsigned long hash_value;
    size_t i = 0;

    while (*password != '\0') {
        hash_value += *password++;
        hash_value += (hash_value << 10);
        hash_value ^= (hash_value >> 6);
    }
    
    hash_value += (hash_value << 3);
    hash_value ^= (hash_value >> 11);
    hash_value += (hash_value << 15);

    for (i = 0; i < HASH_LENGTH - 1; ++i) {
        char c = (char)((hash_value & 0xFF) + 'a');
        hash[i] = c;
        hash_value >>= 8;
    }
    hash[HASH_LENGTH - 1] = '\0';
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[100];
    char password[100];
    char hashed_password[HASH_LENGTH + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);
    
    const char *server = "localhost";
    const char *user = "root";
    const char *password_db = "";
    const char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password_db, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, hashed_password) VALUES ('%s', '%s')",
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User inserted successfully.\n");

    mysql_close(conn);
    return 0;
}