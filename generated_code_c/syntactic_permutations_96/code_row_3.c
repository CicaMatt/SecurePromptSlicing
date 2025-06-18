#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "mysql/mysql.h"

char *salt_gen(void) {
    unsigned char output[SHA256_DIGEST_LENGTH];
    int i;
    for (i = 0; i < 10; ++i) {
        sprintf(output, "%08x", arc4random());
    }
    return (char *)output;
}

int main() {
    MYSQL *conn;
    char username[50];
    char password[256];
    int i = 0;
    printf("Enter your username: ");
    scanf("%s", &username);
    printf("Enter your password: ");
    scanf("%s", &password);
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }
    if (mysql_real_connect(conn, "localhost", "root", "password", "database",
                           0, NULL, 0)) {
        printf("Connected...\n");
        SHA256_CTX ctx;
        char salt[SHA256_DIGEST_LENGTH];
        SHA256_Init(&ctx);
        SHA256_Update(&ctx, password, strlen(password));
        SHA256_Final((unsigned char *)salt, &ctx);
        char *hashed = salt_gen();
        mysql_real_query(conn, "INSERT INTO users (username, hash) VALUES ('%s', '%s')", username, hashed);
    } else {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    mysql_close(conn);
    return 0;
}