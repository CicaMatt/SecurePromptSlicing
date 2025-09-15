#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_image(const char *image_name, const char *base64_data) {
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

    // Prepare and execute SQL query
    char query[1024];
    snprintf(query, sizeof(query), 
             "INSERT INTO images (image_name, image_data) VALUES ('%s', '%s')",
             image_name, base64_data);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Close the connection
    mysql_close(conn);
}

int main() {
    const char *image_name = "example.jpg";
    const char *base64_data = "iVBORw0KGgoAAAANSUhEUgAAAAUA...";
    
    upload_image(image_name, base64_data);

    return 0;
}
