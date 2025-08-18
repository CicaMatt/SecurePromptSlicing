#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SALT_LENGTH 16

void generateSalt(char *salt) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < SALT_LENGTH - 1; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[SALT_LENGTH - 1] = '\0';
}

void hashPassword(const char *password, const char *salt, char *hashedPassword) {
    // Simple hashing simulation using strcat for demonstration purposes
    strcpy(hashedPassword, password);
    strcat(hashedPassword, salt);
}

int storeUser(MYSQL *conn, const char *username, const char *hashedPassword) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    my_bool is_null[2] = {0, 0};
    unsigned long length[2];

    const char *query = "INSERT INTO users (username, password) VALUES (?, ?)";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return -1;
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].length = &length[0];
    length[0] = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)hashedPassword;
    bind[1].length = &length[1];
    length[1] = strlen(hashedPassword);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return -1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return -1;
    }

    mysql_stmt_close(stmt);
    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "test_db", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[100];
    char password[100];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    char salt[SALT_LENGTH + 1];
    generateSalt(salt);

    char hashedPassword[256];
    hashPassword(password, salt, hashedPassword);

    if (storeUser(conn, username, hashedPassword) == -1) {
        fprintf(stderr, "Failed to store user\n");
    } else {
        printf("User registered successfully\n");
    }

    mysql_close(conn);
    return 0;
}