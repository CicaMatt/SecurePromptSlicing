#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "your_db_user"
#define DB_PASS "your_db_pass"
#define DB_NAME "your_db_name"

void hashPassword(const char* input, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(output, &sha256);
}

int checkUsernameExists(MYSQL *conn, const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    mysql_free_result(result);

    return count > 0 ? 1 : 0;
}

int insertUser(MYSQL *conn, const char *username, unsigned char hashedPassword[SHA256_DIGEST_LENGTH], const char *firstName, const char *lastName, const char *email) {
    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%.*s', '%s', '%s', '%s')",
             username,
             SHA256_DIGEST_LENGTH, hashedPassword,
             firstName, lastName, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[50], password[50], firstName[50], lastName[50], email[100];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", firstName);
    printf("Enter last name: ");
    scanf("%49s", lastName);
    printf("Enter email: ");
    scanf("%99s", email);

    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    hashPassword(password, hashedPassword);

    if (checkUsernameExists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        if (insertUser(conn, username, hashedPassword, firstName, lastName, email) == 0) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "Failed to insert user into database.\n");
        }
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}