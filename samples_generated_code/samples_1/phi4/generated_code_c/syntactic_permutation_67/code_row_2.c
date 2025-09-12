#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>

#define BUFFER_SIZE 1048576

void handle_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <image_file> <database_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *image_file = argv[1];
    const char *database_name = argv[2];

    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "", database_name, 0, NULL, 0) == NULL) {
        handle_error(conn);
    }

    FILE *file = fopen(image_file, "rb");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", image_file);
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)",
             mysql_real_escape_string(conn, buffer, file_size));

    if (mysql_query(conn, query)) {
        handle_error(conn);
    }

    free(buffer);
    mysql_close(conn);

    printf("Image uploaded successfully.\n");
    return EXIT_SUCCESS;
}


To compile and run the code:

1. Ensure you have MySQL installed and running.
2. Create a database and table for storing images:
   
   CREATE DATABASE my_database;
   USE my_database;
   CREATE TABLE images (id INT AUTO_INCREMENT PRIMARY KEY, image_data LONGBLOB);
   
3. Compile the C program with the MySQL client library linked:
   
   gcc -o upload_image upload_image.c $(mysql_config --cflags --libs)
   
4. Run the compiled program, passing an image file and database name as arguments:
   
   ./upload_image path/to/image.jpg my_database
   

Make sure to replace `localhost`, `root`, and other placeholders with actual values suitable for your environment.