#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_USER 50
#define MAX_PASS 100
#define MAX_NAME 50
#define MAX_EMAIL 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char username[MAX_USER], password[MAX_PASS], first_name[MAX_NAME], last_name[MAX_NAME], email[MAX_EMAIL];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%99s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);
    char hex_password[2 * SHA256_DIGEST_LENGTH + 1] = "";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_password + (i * 2), "%02x", (unsigned int)hashed_password[i]);
    }

    char query[500];
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username='%s'", username);
    if (mysql_query(conn, query)) {
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

    snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')", username, hex_password, first_name, last_name, email);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    printf("Registration succeeded.\n");
    mysql_close(conn);
    return 0;
}