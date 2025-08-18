#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"

char *hash_password(const char *password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    char *output = (char *)malloc(65 * sizeof(char));
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0';
    return output;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    char username[50], password[50], firstname[50], lastname[50], email[100];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", firstname);
    printf("Enter last name: ");
    scanf("%49s", lastname);
    printf("Enter email: ");
    scanf("%99s", email);

    char check_query[256];
    sprintf(check_query, "SELECT username FROM users WHERE username='%s'", username);
    if (mysql_query(conn, check_query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
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

    char *hashed_password = hash_password(password);
    char insert_query[512];
    sprintf(insert_query, "INSERT INTO users (username, password, firstname, lastname, email) VALUES ('%s', '%s', '%s', '%s', '%s')", 
            username, hashed_password, firstname, lastname, email);

    if (mysql_query(conn, insert_query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(hashed_password);
        mysql_close(conn);
        return 1;
    }

    printf("Registration succeeded.\n");
    free(hashed_password);
    mysql_close(conn);
    return 0;
}