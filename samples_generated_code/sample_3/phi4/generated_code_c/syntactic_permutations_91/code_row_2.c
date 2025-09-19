#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 64

void hash_password(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(outputBuffer, &sha256);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "user_db", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter Username: ");
    fgets(username, USERNAME_LEN, stdin);
    size_t ln = strlen(username) - 1;
    if (ln > 0 && username[ln] == '\n')
        username[ln] = '\0';

    printf("Enter Password: ");
    fgets(password, PASSWORD_LEN, stdin);
    ln = strlen(password) - 1;
    if (ln > 0 && password[ln] == '\n')
        password[ln] = '\0';

    hash_password(password, hashed_password);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", 
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
    return 0;
}
