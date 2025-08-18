#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8192

void store_image_in_database(const char *image_path, const char *db_host, 
                             const char *db_user, const char *db_password,
                             const char *db_name) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open image file");
        exit(EXIT_FAILURE);
    }

    // Get the size of the file
    fseek(file, 0L, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    // Allocate memory for the file content
    unsigned char *buffer = (unsigned char *)malloc(fsize);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read the entire file into buffer
    fread(buffer, 1, fsize, file);

    // Initialize MySQL connection
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        free(buffer);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Connect to the database
    if (mysql_real_connect(conn, db_host, db_user, db_password, 
                           db_name, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        free(buffer);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Prepare and execute the query to insert image data
    const char *query = "INSERT INTO images (image_data) VALUES (?)";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init(), out of memory\n");
        free(buffer);
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare(), INSERT failed\n");
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        free(buffer);
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    // Set up the data binding
    unsigned long lengths[1] = {fsize};
    buffer_type *buffer_type = (buffer_type *)malloc(sizeof(buffer_type));
    if (!buffer_type) {
        perror("Failed to allocate memory");
        free(buffer);
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = buffer;
    bind[0].buffer_length = fsize;
    bind[0].length = &lengths[0];

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        free(buffer);
        free(buffer_type);
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Execute the statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute(), INSERT failed\n");
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        free(buffer);
        free(buffer_type);
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Cleanup and close connections
    mysql_stmt_close(stmt);
    free(buffer);
    free(buffer_type);
    fclose(file);
    mysql_close(conn);

    printf("Image successfully stored in the database.\n");
}

int main(int argc, char **argv) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s <image_path> <db_host> <db_user> <db_password> <db_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *image_path = argv[1];
    const char *db_host = argv[2];
    const char *db_user = argv[3];
    const char *db_password = argv[4];
    const char *db_name = argv[5];

    store_image_in_database(image_path, db_host, db_user, db_password, db_name);

    return EXIT_SUCCESS;
}