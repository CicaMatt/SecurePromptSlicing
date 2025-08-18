#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_LEN 256

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "pass", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    char username[MAX_LEN], password[MAX_LEN], firstname[MAX_LEN], lastname[MAX_LEN], email[MAX_LEN];
    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);
    printf("Enter first name: ");
    scanf("%255s", firstname);
    printf("Enter last name: ");
    scanf("%255s", lastname);
    printf("Enter email: ");
    scanf("%255s", email);

    char check_query[MAX_LEN];
    snprintf(check_query, MAX_LEN, "SELECT COUNT(*) FROM users WHERE username = '%s'", username);
    if (mysql_query(conn, check_query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    mysql_free_result(result);

    if (count > 0) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);
    char hex_password[2 * SHA256_DIGEST_LENGTH + 1] = "";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_password + (i * 2), "%02x", (unsigned int)hashed_password[i]);
    }

    char insert_query[MAX_LEN];
    snprintf(insert_query, MAX_LEN, "INSERT INTO users (username, password, firstname, lastname, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
             username, hex_password, firstname, lastname, email);
    if (mysql_query(conn, insert_query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    printf("Registration succeeded.\n");
    mysql_close(conn);
    return EXIT_SUCCESS;
}