#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"

struct DatabaseConnection {
    MYSQL *conn;
};

void initializeDatabase(struct DatabaseConnection *db) {
    db->conn = mysql_init(NULL);
    if (mysql_real_connect(db->conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        printf("Connected to database\n");
    } else {
        fprintf(stderr, "Error: %s\n", mysql_error(db->conn));
        exit(EXIT_FAILURE);
    }
}

void closeDatabase(struct DatabaseConnection *db) {
    if (db->conn != NULL && mysql_close(db->conn)) {
        fprintf(stderr, "%s\n", mysql_error(db->conn));
    }
}

int isUserModerator(const char *username) {
    struct DatabaseConnection db;
    initializeDatabase(&db);
    
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username='%s' AND moderator=1;", username);

    if (mysql_query(db.conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(db->conn));
        closeDatabase(&db);
        return 0;
    }

    MYSQL_RES *result = mysql_store_result(db.conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(db->conn));
        closeDatabase(&db);
        return 0;
    }
    
    MYSQL_ROW row = mysql_fetch_row(result);
    int isModerator = atoi(row[0]);
    
    mysql_free_result(result);
    closeDatabase(&db);

    return isModerator > 0;
}

void handleRequest(const char *username) {
    if (isUserModerator(username)) {
        printf("The user %s is a moderator.\n", username);
    } else {
        printf("The user %s is not a moderator.\n", username);
    }
}

int main() {
    // Example usage
    handleRequest("example_user");

    return 0;
}


Make sure to link against the MySQL client library by compiling with `-lmysqlclient`:


gcc -o app your_source_file.c $(mysql_config --cflags --libs)