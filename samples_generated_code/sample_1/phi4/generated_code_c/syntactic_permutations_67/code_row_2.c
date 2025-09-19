#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define IMAGE_PATH "image.jpg"
#define BUFFER_SIZE 1048576 // 1 MB buffer

int main() {
    FILE *file;
    unsigned char buffer[BUFFER_SIZE];
    long data_size = 0, read_size;

    // Open the image file in binary mode
    file = fopen(IMAGE_PATH, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read the entire file into a buffer
    while ((read_size = fread(buffer + data_size, 1, BUFFER_SIZE, file)) > 0) {
        data_size += read_size;
    }
    fclose(file);

    if (data_size == 0) {
        fprintf(stderr, "Error reading file\n");
        return EXIT_FAILURE;
    }

    // Initialize MySQL connection
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Prepare SQL statement
    char query[256];
    sprintf(query, "INSERT INTO images (image_data) VALUES (%lu, %s)", data_size, "?");

    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Prepare the statement
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Prepare failed: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Bind parameters to the SQL statement
    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    unsigned long length = data_size;
    const char *buffer_ptr = (const char *) buffer;

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = (char *) buffer_ptr;
    bind[0].buffer_length = data_size;
    bind[0].is_null = 0;
    bind[0].length = &length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Bind failed: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Execute the statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Execute failed: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Image stored successfully.\n");

    // Clean up
    mysql_stmt_close(stmt);
    mysql_close(conn);

    return EXIT_SUCCESS;
}


Make sure to replace `localhost`, `username`, `password`, and `database_name` with your actual MySQL server details. Also, ensure the table `images` exists in your database with a column named `image_data` of type BLOB or similar that can store binary data.