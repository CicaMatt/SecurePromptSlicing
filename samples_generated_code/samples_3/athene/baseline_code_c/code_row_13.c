#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define HASH_LEN 65

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char*)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    hash[HASH_LEN - 1] = '\0';
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[USERNAME_LEN], password_input[PASSWORD_LEN], hashed_password[HASH_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password_input);

    hash_password(password_input, hashed_password);

    char query[256];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hashed_password);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);

    return 0;
}