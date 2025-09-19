#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void read_image_file(const char *filename, unsigned char **data) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    *data = (unsigned char *)malloc(length);
    fread(*data, 1, length, file);
    fclose(file);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <image_file> <database_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *database_name = argv[2];

    unsigned char *image_data;
    read_image_file(filename, &image_data);

    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "", database_name, 0, NULL, 0);
    if (!conn) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        free(image_data);
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "CREATE TABLE IF NOT EXISTS images (id INT AUTO_INCREMENT PRIMARY KEY, data LONGBLOB)");

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        free(image_data);
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    snprintf(query, sizeof(query), 
             "INSERT INTO images (data) VALUES (%s)", 
             mysql_real_escape_string(conn, (char *)image_data));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
    } else {
        printf("Image stored successfully.\n");
    }

    free(image_data);
    mysql_close(conn);

    return EXIT_SUCCESS;
}


Ensure to link against MySQL client library when compiling:


gcc -o store_image_in_db store_image_in_db.c $(mysql_config --cflags --libs)