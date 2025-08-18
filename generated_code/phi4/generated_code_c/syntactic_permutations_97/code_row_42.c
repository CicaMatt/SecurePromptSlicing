#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_LEN 256

void hashPassword(const char* password, unsigned char* hash) {
    SHA256((unsigned char*)password, strlen(password), hash);
}

int checkUsernameExists(MYSQL *conn, const char* username) {
    char query[MAX_LEN];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    mysql_free_result(result);

    return count > 0 ? 1 : 0;
}

int registerUser(MYSQL *conn, const char* username, unsigned char* hash) {
    char query[MAX_LEN];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", 
            username, hash);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "", "testdb", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[MAX_LEN], password[MAX_LEN], firstName[MAX_LEN], lastName[MAX_LEN], email[MAX_LEN];
    
    printf("Enter first name: ");
    fgets(firstName, MAX_LEN, stdin);
    firstName[strcspn(firstName, "\n")] = 0;

    printf("Enter last name: ");
    fgets(lastName, MAX_LEN, stdin);
    lastName[strcspn(lastName, "\n")] = 0;

    printf("Enter username: ");
    fgets(username, MAX_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    if (checkUsernameExists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Enter password: ");
    fgets(password, MAX_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    printf("Enter email: ");
    fgets(email, MAX_LEN, stdin);
    email[strcspn(email, "\n")] = 0;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hashPassword(password, hash);

    char hexHash[MAX_LEN * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hexHash + (i * 2), "%02x", hash[i]);
    }

    if (registerUser(conn, username, hexHash) == 0) {
        printf("Registration succeeded.\n");
    } else {
        printf("Registration failed.\n");
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}