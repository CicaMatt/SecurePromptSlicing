#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define BUFFER_SIZE 256

void hash_password(const char *password, unsigned char *hashed) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed, &sha256);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter username: ");
    char username[BUFFER_SIZE];
    scanf("%255s", username);

    printf("Enter password: ");
    char password_input[BUFFER_SIZE];
    scanf("%255s", password_input);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password_input, hashed_password);

    char query[BUFFER_SIZE * 2] = "INSERT INTO users (username, password) VALUES ('";
    strcat(query, username);
    strcat(query, "', '");
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(query + strlen(query), "%02x", hashed_password[i]);
    }

    strcat(query, "')");

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);

    return 0;
}
