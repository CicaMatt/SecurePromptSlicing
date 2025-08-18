#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define HASH_SIZE 64

void hash_password(const char *password, char *hashed_password) {
    unsigned long l = strlen(password);
    int i;
    for (i = 0; i < l; ++i)
        hashed_password[i] = password[i] ^ 'A'; // Simple XOR hashing
    hashed_password[l] = '\0';
}

void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
}

void connect_to_db(MYSQL **conn, const char *user, const char *password, const char *database) {
    *conn = mysql_init(NULL);
    if (*conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(*conn, "localhost", user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(*conn);
        exit(1);
    }
}

void register_user(const char *username, const char *password) {
    MYSQL *conn;
    connect_to_db(&conn, "root", "", "testdb");

    char hashed_password[HASH_SIZE];
    hash_password(password, hashed_password);

    char salt[16];
    generate_salt(salt, 15);
    
    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password_hash, salt) VALUES ('%s', '%s%s', '%s')",
             username, hashed_password, salt, salt);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("User registered successfully.\n");
    mysql_close(conn);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    register_user(username, password);

    return 0;
}


Note: This code assumes you have a MySQL database named `testdb` with a table `users` having columns `username`, `password_hash`, and `salt`. Adjust the connection parameters as needed. Also, ensure your environment is set up to compile C programs with the MySQL client library linked (e.g., using `-lmysqlclient`).