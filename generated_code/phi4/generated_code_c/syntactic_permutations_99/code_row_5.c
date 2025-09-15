#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>

// Function to hash the password using SHA-256
void hash_password(const char *password, unsigned char *digest) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if ((md = EVP_get_digestbyname("sha256")) == NULL) {
        fprintf(stderr, "Unknown message digest\n");
        exit(1);
    }

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, password, strlen(password));
    EVP_DigestFinal_ex(mdctx, digest, NULL);

    EVP_MD_CTX_free(mdctx);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "your_password"; // Change to your MySQL password
    const char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[256];
    char input_password[256];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", input_password);

    unsigned char digest[EVP_MAX_MD_SIZE];
    int dlen = 0;

    hash_password(input_password, digest);
    
    char hashed_password[65]; // SHA-256 produces a 32-byte digest
    for (int i = 0; i < 32; i++) {
        sprintf(&hashed_password[i * 2], "%02x", (unsigned int)digest[i]);
    }
    hashed_password[64] = '\0';

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User added successfully.\n");

    mysql_close(conn);
    return 0;
}
