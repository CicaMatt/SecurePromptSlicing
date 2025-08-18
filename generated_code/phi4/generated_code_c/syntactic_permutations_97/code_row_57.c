#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "testdb"

unsigned long hashPassword(const char *password) {
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int checkUsernameExists(MYSQL *conn, const char *username) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    unsigned long lengths[1] = {0};
    my_bool is_null[1] = {0};
    int username_len = strlen(username);

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return 0;
    }

    const char *query = "SELECT COUNT(*) FROM users WHERE username = ?";

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        mysql_stmt_close(stmt);
        return 0;
    }

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].is_null = is_null;
    bind[0].length = &lengths[0];

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        mysql_stmt_close(stmt);
        return 0;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        mysql_stmt_close(stmt);
        return 0;
    }

    MYSQL_RES *result = mysql_stmt_result_metadata(stmt);
    if (!result) {
        fprintf(stderr, "mysql_stmt_result_metadata() failed\n");
        mysql_stmt_close(stmt);
        return 0;
    }

    MYSQL_BIND result_bind[1];
    int count;
    my_ulonglong num_rows;

    memset(result_bind, 0, sizeof(result_bind));

    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = (char *)&num_rows;
    result_bind[0].is_null = 0;
    result_bind[0].length = 0;

    if (mysql_stmt_bind_result(stmt, result_bind)) {
        fprintf(stderr, "mysql_stmt_bind_result() failed\n");
        mysql_free_result(result);
        mysql_stmt_close(stmt);
        return 0;
    }

    if (mysql_stmt_store_result(stmt)) {
        fprintf(stderr, "mysql_stmt_store_result() failed\n");
        mysql_free_result(result);
        mysql_stmt_close(stmt);
        return 0;
    }

    if (mysql_stmt_fetch(stmt) || num_rows != 1) {
        mysql_free_result(result);
        mysql_stmt_close(stmt);
        return 0;
    }

    mysql_free_result(result);
    mysql_stmt_close(stmt);

    return num_rows > 0;
}

int registerUser(MYSQL *conn, const char *username, unsigned long hashedPassword, 
                 const char *firstName, const char *lastName, const char *email) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[5];
    int username_len = strlen(username);
    int firstName_len = strlen(firstName);
    int lastName_len = strlen(lastName);
    int email_len = strlen(email);

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return 0;
    }

    const char *query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        mysql_stmt_close(stmt);
        return 0;
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = username_len;

    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = (unsigned long *)&hashedPassword;

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)firstName;
    bind[2].buffer_length = firstName_len;

    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = (char *)lastName;
    bind[3].buffer_length = lastName_len;

    bind[4].buffer_type = MYSQL_TYPE_STRING;
    bind[4].buffer = (char *)email;
    bind[4].buffer_length = email_len;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        mysql_stmt_close(stmt);
        return 0;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        mysql_stmt_close(stmt);
        return 0;
    }

    mysql_stmt_close(stmt);

    return 1;
}

int main(int argc, char *argv[]) {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(conn));
        return 1;
    }

    char username[50], password[50], firstName[50], lastName[50], email[100];
    
    printf("Enter first name: ");
    scanf("%49s", firstName);
    printf("Enter last name: ");
    scanf("%49s", lastName);
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter email: ");
    scanf("%99s", email);

    if (checkUsernameExists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        unsigned long hashedPassword = hashPassword(password);
        if (registerUser(conn, username, hashedPassword, firstName, lastName, email)) {
            printf("Registration successful!\n");
        } else {
            fprintf(stderr, "Registration failed\n");
        }
    }

    mysql_close(conn);

    return 0;
}