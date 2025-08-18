#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 65536

void print_error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <image_path> <database_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *image_path = argv[1];
    const char *database_name = argv[2];

    // Open image file
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        print_error("Error opening image file.");
    }

    // Determine the size of the file
    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    // Read binary data from the file into a buffer
    char *buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        print_error("Memory allocation failed.");
    }

    fread(buffer, 1, file_size, file);
    fclose(file);
    buffer[file_size] = '\0'; // Null-terminate for safety

    // Initialize MySQL connection
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        print_error("MySQL initialization failed.");
    }

    // Connect to the database server
    if (mysql_real_connect(conn, "localhost", "user", "password", NULL, 0, NULL, 0) == NULL) {
        print_error(mysql_error(conn));
    }

    // Create a new database
    char query[256];
    snprintf(query, sizeof(query), "CREATE DATABASE IF NOT EXISTS %s;", database_name);
    if (mysql_query(conn, query)) {
        print_error(mysql_error(conn));
    }

    // Select the newly created database
    mysql_select_db(conn, database_name);

    // Create a table to store images if it does not exist
    snprintf(query, sizeof(query), "CREATE TABLE IF NOT EXISTS images (id INT AUTO_INCREMENT PRIMARY KEY, image LONGBLOB);");
    if (mysql_query(conn, query)) {
        print_error(mysql_error(conn));
    }

    // Prepare an INSERT statement to add the image data
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        print_error("MySQL statement initialization failed.");
    }

    snprintf(query, sizeof(query), "INSERT INTO images (image) VALUES (%s);");
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        print_error(mysql_error(conn));
    }

    // Bind the parameter
    MYSQL_BIND bind[1];
    my_bool is_null = 0;
    unsigned long length = file_size;

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = (char *)buffer;
    bind[0].is_null = &is_null;
    bind[0].length = &length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        print_error(mysql_error(conn));
    }

    // Execute the statement
    if (mysql_stmt_execute(stmt)) {
        print_error(mysql_error(conn));
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);

    free(buffer);
    printf("Image successfully stored in database.\n");

    return EXIT_SUCCESS;
}