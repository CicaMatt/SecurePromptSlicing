#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void store_image_in_db(const char *filename, const char *db_host, const char *db_user, const char *db_password, const char *db_name) {
    MYSQL *conn;
    FILE *file;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, db_host, db_user, db_password, db_name, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    // Open the image file
    file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Prepare SQL statement to insert binary data
    const char *sql = "INSERT INTO images (image_data) VALUES (?)";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "MySQL stmt init error: %s\n", mysql_error(conn));
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        fprintf(stderr, "MySQL prepare statement error: %s\n", mysql_error(conn));
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Create and bind buffer for image data
    MYSQL_BIND bind[1];
    my_bool is_null = 0;
    unsigned long length;

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = (char *)malloc(BUFFER_SIZE);
    if (!bind[0].buffer) {
        fprintf(stderr, "Memory allocation error\n");
        mysql_stmt_close(stmt);
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    bind[0].buffer_length = BUFFER_SIZE;
    bind[0].length = &length;
    bind[0].is_null = &is_null;

    // Bind the buffer to the statement
    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "MySQL stmt bind param error: %s\n", mysql_error(conn));
        free(bind[0].buffer);
        mysql_stmt_close(stmt);
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Read the file and send to MySQL
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        length = bytes_read;
        if (mysql_stmt_send_long_data(stmt, 0, buffer, length)) {
            fprintf(stderr, "MySQL stmt send long data error: %s\n", mysql_error(conn));
            free(bind[0].buffer);
            mysql_stmt_close(stmt);
            fclose(file);
            mysql_close(conn);
            exit(EXIT_FAILURE);
        }
    }

    // Execute the statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "MySQL stmt execute error: %s\n", mysql_error(conn));
    } else {
        printf("Image stored successfully in database.\n");
    }

    // Clean up
    free(bind[0].buffer);
    mysql_stmt_close(stmt);
    fclose(file);
    mysql_close(conn);
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s <image_file> <db_host> <db_user> <db_password> <db_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *db_host = argv[2];
    const char *db_user = argv[3];
    const char *db_password = argv[4];
    const char *db_name = argv[5];

    store_image_in_db(filename, db_host, db_user, db_password, db_name);

    return EXIT_SUCCESS;
}