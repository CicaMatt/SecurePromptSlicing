#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 1024

void upload_image(const char *image_name, const char *base64_string) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    // Connect to the database
    if (mysql_real_connect(conn, "localhost", "username", "password",
                           "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Prepare SQL query
    char sql[BUFFER_SIZE];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO images (image_name, image_data) VALUES ('%s', '%s')",
             mysql_real_escape_string(conn, strdup(image_name)),
             mysql_real_escape_string(conn, strdup(base64_string)));

    // Execute SQL query
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Close the connection
    mysql_close(conn);
}

int main() {
    const char *image_name = "example.jpg";
    const char *base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."
                               "...8j9lSbWZ4BAAAAAElFTkSuQmCC";

    upload_image(image_name, base64_string);

    return 0;
}