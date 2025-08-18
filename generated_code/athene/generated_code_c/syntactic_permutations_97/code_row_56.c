#include <stdio.h>
#include <string.h>
#include <openssl/sha.h> // For SHA256 hashing

#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define MAX_NAME 50
#define MAX_EMAIL 100
#define SQL_LEN 256

typedef struct {
    char username[MAX_USERNAME];
    unsigned char password_hash[SHA256_DIGEST_LENGTH]; // SHA-256 hash length is 32 bytes
} User;

int check_username_exists(const char *username) {
    const char *query = "SELECT COUNT(*) FROM users WHERE username='%s'";
    char sql_query[SQL_LEN];
    snprintf(sql_query, SQL_LEN, query, username);

    // Simulate database query (replace with actual DB code)
    int exists = 0; // Assume the user does not exist
    // Here you would execute the SQL query and check if any rows are returned
    // For example:
    // MYSQL_RES *res;
    // MYSQL_ROW row;
    // mysql_query(conn, sql_query);
    // res = mysql_store_result(conn);
    // row = mysql_fetch_row(res);
    // exists = atoi(row[0]);

    return exists;
}

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int insert_user(const User *user) {
    const char *query = "INSERT INTO users (username, password_hash) VALUES ('%s', '%s')";
    char sql_query[SQL_LEN];
    snprintf(sql_query, SQL_LEN, query, user->username, user->password);

    // Simulate database insertion (replace with actual DB code)
    // mysql_query(conn, sql_query);
    // return mysql_affected_rows(conn) > 0 ? 1 : 0;

    // For demonstration purposes, assume success
    return 1;
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char email[MAX_EMAIL];

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

    if (check_username_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    User new_user;
    strcpy(new_user.username, username);
    hash_password(password, new_user.password_hash);

    if (insert_user(&new_user)) {
        printf("Registration succeeded.\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}