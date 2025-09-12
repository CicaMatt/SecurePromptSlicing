#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASS ""
#define MYSQL_DB   "user_db"

void hash_password(const char *password, char *hashed_password) {
    // Simple hashing for demonstration (not secure)
    unsigned long int hashed = 5381;
    int c;

    while ((c = *password++))
        hashed = ((hashed << 5) + hashed) + c; /* hash * 33 + c */

    sprintf(hashed_password, "%lu", hashed);
}

int check_username_exists(MYSQL *conn, const char *username) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    my_bool is_null = 0;
    unsigned long length = 0;
    int username_exists = 0;

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init(), out of memory\n");
        return -1;
    }

    char *query = "SELECT COUNT(*) FROM users WHERE username = ?";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare(), failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].is_null = &is_null;
    bind[0].length = &length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute(), FAILED\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    unsigned long count_length = 0;
    int param_count = 0;

    if (mysql_stmt_bind_result(stmt, &username_exists) || mysql_stmt_fetch(stmt)) {
        fprintf(stderr, "Could not bind or fetch result\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    mysql_stmt_close(stmt);

    return username_exists > 0 ? 1 : 0;
}

int register_user(MYSQL *conn, const char *username, const char *password, const char *first_name, 
                  const char *last_name, const char *email) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[5];
    my_bool is_null = 0;
    unsigned long length = 0;

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init(), out of memory\n");
        return -1;
    }

    char *query = "INSERT INTO users (username, password_hashed, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare(), failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    memset(bind, 0, sizeof(bind));

    char hashed_password[20];
    hash_password(password, hashed_password);

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].is_null = &is_null;
    bind[0].length = &length;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)hashed_password;
    bind[1].is_null = &is_null;
    bind[1].length = &length;

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)first_name;
    bind[2].is_null = &is_null;
    bind[2].length = &length;

    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = (char *)last_name;
    bind[3].is_null = &is_null;
    bind[3].length = &length;

    bind[4].buffer_type = MYSQL_TYPE_STRING;
    bind[4].buffer = (char *)email;
    bind[4].is_null = &is_null;
    bind[4].length = &length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute(), FAILED\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    mysql_stmt_close(stmt);

    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "Database connection failed: %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    char username[50], password[20], first_name[50], last_name[50], email[100];

    printf("Enter Username: ");
    scanf("%49s", username);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        printf("Enter Password: ");
        scanf("%19s", password);
        
        printf("Enter First Name: ");
        scanf("%49s", first_name);

        printf("Enter Last Name: ");
        scanf("%49s", last_name);

        printf("Enter Email: ");
        scanf("%99s", email);

        if (register_user(conn, username, password, first_name, last_name, email) == 0) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "Failed to register user.\n");
        }
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}