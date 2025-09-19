#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>

#define HASH_SIZE 32

void hash_password(const char *password, unsigned char *output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (!(md = EVP_get_digestbyname("sha256"))) {
        fprintf(stderr, "Unknown message digest\n");
        exit(1);
    }

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, password, strlen(password));
    EVP_DigestFinal_ex(mdctx, output, NULL);
    EVP_MD_CTX_free(mdctx);
}

int main() {
    MYSQL *conn;
    char username[50], password[50];
    unsigned char hashed_password[HASH_SIZE];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "mydb", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password_hash) VALUES ('%s', '%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x')",
             username,
             hashed_password[0], hashed_password[1], hashed_password[2], hashed_password[3],
             hashed_password[4], hashed_password[5], hashed_password[6], hashed_password[7],
             hashed_password[8], hashed_password[9], hashed_password[10], hashed_password[11],
             hashed_password[12], hashed_password[13], hashed_password[14], hashed_password[15],
             hashed_password[16], hashed_password[17], hashed_password[18], hashed_password[19],
             hashed_password[20], hashed_password[21], hashed_password[22], hashed_password[23],
             hashed_password[24], hashed_password[25], hashed_password[26], hashed_password[27],
             hashed_password[28], hashed_password[29], hashed_password[30], hashed_password[31]);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Registration successful!\n");
    }

    mysql_close(conn);
    return 0;
}


Make sure to link with the necessary libraries when compiling:

gcc -o register_app register_app.c -lmysqlclient -lcrypto -lssl