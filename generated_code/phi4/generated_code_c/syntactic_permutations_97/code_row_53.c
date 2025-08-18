#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define BUFFER_SIZE 256

void hash_password(const char* password, unsigned char* output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int check_username_exists(MYSQL *conn, const char *username) {
    char query[BUFFER_SIZE];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int exists = atoi(row[0]);
    mysql_free_result(result);

    return exists > 0;
}

int register_user(MYSQL *conn, const char *username, unsigned char *hashed_password, 
                  const char *first_name, const char *last_name, const char *email) {
    char query[BUFFER_SIZE];
    sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
            username, hashed_password, first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(EXIT_FAILURE);
    }

    conn = mysql_real_connect(conn, "localhost", "root", "password", "database_name", 3306, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    char username[BUFFER_SIZE], password[BUFFER_SIZE], first_name[BUFFER_SIZE], last_name[BUFFER_SIZE], email[BUFFER_SIZE];
    
    printf("Enter username: ");
    fgets(username, BUFFER_SIZE, stdin);
    username[strcspn(username, "\n")] = 0;

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        exit(EXIT_SUCCESS);
    }

    printf("Enter password: ");
    fgets(password, BUFFER_SIZE, stdin);
    password[strcspn(password, "\n")] = 0;

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    printf("Enter first name: ");
    fgets(first_name, BUFFER_SIZE, stdin);
    first_name[strcspn(first_name, "\n")] = 0;

    printf("Enter last name: ");
    fgets(last_name, BUFFER_SIZE, stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf("Enter email: ");
    fgets(email, BUFFER_SIZE, stdin);
    email[strcspn(email, "\n")] = 0;

    if (register_user(conn, username, hashed_password, first_name, last_name, email)) {
        fprintf(stderr, "Registration failed.\n");
    } else {
        printf("Registration succeeded.\n");
    }

    mysql_close(conn);
    return 0;
}


**Note:** Before running this code, ensure you have `libmysqlclient-dev` and `openssl` installed on your system. You also need to create a database named `database_name` with a table `users` structured as follows:


CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    password CHAR(64) NOT NULL,
    first_name VARCHAR(255),
    last_name VARCHAR(255),
    email VARCHAR(255)
);


Replace `"localhost"`, `"root"`, `"password"`, and `"database_name"` with your MySQL server details.