#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define IMAGE_BUFFER_SIZE 1048576 // 1MB buffer size

void store_image_in_database(const char *image_path, const char *db_host, const char *db_user, const char *db_password, const char *db_name);

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *db_host = "localhost";
    const char *db_user = "root";
    const char *db_password = "";
    const char *db_name = "your_database_name";

    store_image_in_database(argv[1], db_host, db_user, db_password, db_name);

    return EXIT_SUCCESS;
}

void store_image_in_database(const char *image_path, const char *db_host, const char *db_user, const char *db_password, const char *db_name) {
    MYSQL *conn;
    FILE *file;
    unsigned long file_size;
    unsigned char buffer[IMAGE_BUFFER_SIZE];
    size_t bytes_read;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, db_host, db_user, db_password, db_name, 0, NULL, 0)) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    file = fopen(image_path, "rb");
    if (!file) {
        perror("Error opening image file");
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data, size) VALUES (%s, %lu)", 
             mysql_real_escape_string(conn, buffer, fread(buffer, 1, IMAGE_BUFFER_SIZE, file)), file_size);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error executing query: %s\n", mysql_error(conn));
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = fread(buffer, 1, IMAGE_BUFFER_SIZE, file))) {
        snprintf(query, sizeof(query), "UPDATE images SET image_data = CONCAT(image_data, %s) WHERE size = %lu", 
                 mysql_real_escape_string(conn, buffer, bytes_read), file_size);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Error executing query: %s\n", mysql_error(conn));
            fclose(file);
            mysql_close(conn);
            exit(EXIT_FAILURE);
        }
    }

    printf("Image successfully stored in database.\n");

    fclose(file);
    mysql_close(conn);
}


Note: Ensure you have the necessary MySQL C API library installed and linked while compiling this code. Replace `your_database_name` with your actual database name, and configure the correct host, user, password, etc., as needed. The table `images` should be pre-created in the database with columns `image_data (LONGBLOB)` and `size (BIGINT)`.