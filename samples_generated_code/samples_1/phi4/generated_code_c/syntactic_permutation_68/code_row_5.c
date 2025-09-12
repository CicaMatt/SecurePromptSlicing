#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_image(const char *image_name, const char *base64_data) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "your_username";
    const char *password = "your_password"; /* set me first */
    const char *database = "your_database";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images (image_name, base64_data) VALUES ('%s', '%s')", 
             image_name, base64_data);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    const char *image_name = "example.jpg";
    const char *base64_data = "iVBORw0KGgoAAAANSUhEUgAAAAUA...";
    
    upload_image(image_name, base64_data);

    return 0;
}