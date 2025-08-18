#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_LEN 256

void hash_password(const char *password, unsigned char *hashed_password) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

int check_username_exists(MYSQL *conn, const char *username) {
    char query[MAX_LEN];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username = '%s'", username);
    
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

void register_user(MYSQL *conn, const char *username, unsigned char hashed_password[], 
                   const char *first_name, const char *last_name, const char *email) {
    char query[MAX_LEN];
    
    sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) "
                   "VALUES ('%s', '%s', '%s', '%s', '%s')",
            username,
            sha256_to_hex(hashed_password),
            first_name,
            last_name,
            email);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Registration succeeded.\n");
    }
}

char *sha256_to_hex(unsigned char hashed_password[]) {
    static char hex_str[65];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hex_str + (i * 2), "%02x", hashed_password[i]);
    }
    hex_str[64] = '\0';
    return hex_str;
}

void register_page() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "test_db", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[MAX_LEN], password[MAX_LEN], first_name[MAX_LEN], last_name[MAX_LEN], email[MAX_LEN];
    
    printf("Enter username: ");
    scanf("%255s", username);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        exit(1);
    }
    
    printf("Enter password: ");
    scanf("%255s", password);
    
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    printf("Enter first name: ");
    scanf("%255s", first_name);
    
    printf("Enter last name: ");
    scanf("%255s", last_name);
    
    printf("Enter email: ");
    scanf("%255s", email);
    
    register_user(conn, username, hashed_password, first_name, last_name, email);

    mysql_close(conn);
}

int main() {
    register_page();
    return 0;
}