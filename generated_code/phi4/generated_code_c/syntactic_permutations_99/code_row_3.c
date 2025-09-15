#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_KEY "your-secret-key"

void hash_password(const char *password, char *hashed) {
    // Simple XOR-based hashing for demonstration purposes (not secure)
    size_t len = strlen(password);
    for(size_t i = 0; i < len; ++i) {
        hashed[i] = password[i] ^ HASH_KEY[i % sizeof(HASH_KEY)];
    }
    hashed[len] = '\0';
}

int main() {
    char username[50];
    char password[50];
    char hashed_password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);

    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    printf("User inserted successfully.\n");

    mysql_close(conn);
    return 0;
}
