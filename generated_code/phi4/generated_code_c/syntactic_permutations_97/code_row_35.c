#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function to hash the password (simple example, use stronger hashing in production)
void simple_hash(char *input, char *output) {
    for (int i = 0; input[i] != '\0'; ++i) {
        output[i] = input[i] + 1; // Simple Caesar cipher for demonstration
    }
    output[strlen(input)] = '\0';
}

// Function to check if username exists in the database
int user_exists(MYSQL *conn, const char *username) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    unsigned long lengths[1] = {0};
    my_bool is_nulls[1] = {0};

    char query[] = "SELECT COUNT(*) FROM users WHERE username=?";
    
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        return -1;
    }

    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].is_null = &is_nulls[0];
    bind[0].length = &lengths[0];

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        return -1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        return -1;
    }

    int count = 0;
    unsigned long result_len;
    char *result_buf;

    if (mysql_stmt_bind_result(stmt, &count)) {
        fprintf(stderr, "mysql_stmt_bind_result() failed\n");
        return -1;
    }

    if (mysql_stmt_store_result(stmt) && mysql_stmt_fetch(stmt)) {
        fprintf(stderr, "mysql_stmt_fetch() failed\n");
        return -1;
    }

    mysql_stmt_close(stmt);

    return count > 0 ? 1 : 0;
}

// Function to register a new user
int register_user(MYSQL *conn, const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[5];
    unsigned long lengths[5] = {0};
    my_bool is_nulls[5] = {0};

    char query[] = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        return -1;
    }

    char hashed_password[256];
    simple_hash((char *)password, hashed_password);

    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].is_null = &is_nulls[0];
    bind[0].length = &lengths[0];

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = hashed_password;
    bind[1].is_null = &is_nulls[1];
    bind[1].length = &lengths[1];

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)first_name;
    bind[2].is_null = &is_nulls[2];
    bind[2].length = &lengths[2];

    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = (char *)last_name;
    bind[3].is_null = &is_nulls[3];
    bind[3].length = &lengths[3];

    bind[4].buffer_type = MYSQL_TYPE_STRING;
    bind[4].buffer = (char *)email;
    bind[4].is_null = &is_nulls[4];
    bind[4].length = &lengths[4];

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        return -1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        return -1;
    }

    mysql_stmt_close(stmt);
    return 0;
}

int main(int argc, char *argv[]) {
    MYSQL *conn;

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "testdb", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[256], password[256], first_name[256], last_name[256], email[256];
    
    printf("Enter Username: ");
    scanf("%255s", username);
    printf("Enter Password: ");
    scanf("%255s", password);
    printf("Enter First Name: ");
    scanf("%255s", first_name);
    printf("Enter Last Name: ");
    scanf("%255s", last_name);
    printf("Enter Email: ");
    scanf("%255s", email);

    if (user_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        if (register_user(conn, username, password, first_name, last_name, email) == 0) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "Failed to register user.\n");
        }
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}