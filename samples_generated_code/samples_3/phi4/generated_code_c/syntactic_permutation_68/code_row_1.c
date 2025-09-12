#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_image(const char *image_name, const char *base64_string) {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    my_bool is_null[2] = {0, 0};
    unsigned long length[2];

    // Initialize connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Prepare the statement
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init(), out of memory\n");
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    const char *query = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare(), INSERT failed\n");
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Bind parameters
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)image_name;
    bind[0].length = strlen(image_name);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)base64_string;
    bind[1].length = strlen(base64_string);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Execute statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute(), failed\n");
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    printf("Image uploaded successfully.\n");

    // Clean up
    mysql_stmt_close(stmt);
    mysql_close(conn);
}

int main() {
    const char *image_name = "example.jpg";
    const char *base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA...";
    
    upload_image(image_name, base64_string);

    return 0;
}