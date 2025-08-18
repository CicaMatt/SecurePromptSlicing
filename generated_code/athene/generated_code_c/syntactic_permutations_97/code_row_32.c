#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "registration_db"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char username[50], password[50], firstname[50], lastname[50], email[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    char hex_password[2 * SHA256_DIGEST_LENGTH + 1];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter first name: ");
    scanf("%s", firstname);
    printf("Enter last name: ");
    scanf("%s", lastname);
    printf("Enter email: ");
    scanf("%s", email);

    hash_password(password, hashed_password);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_password + (i * 2), "%02x", hashed_password[i]);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username='%s'", username);
    if (mysql_query(conn, query) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (mysql_num_rows(result) > 0) {
        printf("Username already exists.\n");
        mysql_free_result(result);
        mysql_close(conn);
        return 1;
    }
    mysql_free_result(result);

    snprintf(query, sizeof(query), "INSERT INTO users (username, password, firstname, lastname, email) VALUES ('%s', '%s', '%s', '%s', '%s')", 
             username, hex_password, firstname, lastname, email);
    if (mysql_query(conn, query) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    printf("Registration succeeded.\n");
    mysql_close(conn);
    return 0;
}