#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <mysql/mysql.h>
int main() {
    MYSQL mysql;
    char username[100], password[100];
    printf("Username: ");
    scanf("%s", username);
    printf("\nPassword: ");
    scanf("%s", password);
    // md5 hashing
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5((const unsigned char *)password, strlen(password), result);
    char hashed_pwd[33];
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(&hashed_pwd[i*2], "%02x", (unsigned int)result[i]);
    }
    // insert into database
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "root", "password", "database", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        return EXIT_FAILURE;
    }
    char query[250];
    sprintf(query, "insert into users (username, password) values ('%s', '%s')", username, hashed_pwd);
    if (mysql_query(&mysql, query)) {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        return EXIT_FAILURE;
    }
    printf("Registration successful!\n");
    return 0;
}