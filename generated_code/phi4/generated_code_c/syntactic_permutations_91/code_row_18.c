#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define HASH_SIZE 40

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA1_DIGEST_LENGTH];
    SHA1((unsigned char *)password, strlen(password), hash);

    for (int i = 0; i < SHA1_DIGEST_LENGTH; i++) {
        sprintf(&hashed_password[i*2], "%02x", hash[i]);
    }
    hashed_password[HASH_SIZE] = '\0';
}

void register_user(const char *name, const char *password) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char hashed_password[HASH_SIZE + 1];
    hash_password(password, hashed_password);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (name, password) VALUES ('%s', '%s')",
             name, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
}

int main() {
    char name[100];
    char password[100];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    register_user(name, password);

    return 0;
}
