#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define IMAGE_FILE "image.jpg"
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "testdb"

int main() {
    FILE *file;
    unsigned char buffer[8192];
    size_t bytesRead, totalBytes = 0;
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    my_bool is_null = 0;

    // Open the image file
    file = fopen(IMAGE_FILE, "rb");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Connect to the database
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        fclose(file);
        return EXIT_FAILURE;
    }

    // Prepare SQL statement
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        mysql_close(conn);
        fclose(file);
        return EXIT_FAILURE;
    }

    const char *query = "INSERT INTO images (image_data) VALUES (?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        fclose(file);
        return EXIT_FAILURE;
    }

    // Bind parameter
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = buffer;
    bind[0].buffer_length = sizeof(buffer);
    bind[0].is_null = &is_null;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        fclose(file);
        return EXIT_FAILURE;
    }

    // Read and insert image data in chunks
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file))) {
        totalBytes += bytesRead;

        if (mysql_stmt_send_long_data(stmt, 0, buffer, bytesRead)) {
            fprintf(stderr, "mysql_stmt_send_long_data() failed\n");
            mysql_stmt_close(stmt);
            mysql_close(conn);
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    // Execute statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("Image uploaded successfully.\n");

    // Cleanup
    mysql_stmt_close(stmt);
    mysql_close(conn);
    fclose(file);

    return EXIT_SUCCESS;
}