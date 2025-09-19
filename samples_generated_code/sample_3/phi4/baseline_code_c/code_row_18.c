#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define SERVER "localhost"
#define DATABASE "testdb"
#define TABLE "images"
#define USER "root"
#define PASSWORD ""

void load_image(const char *filename, unsigned char **data, size_t *size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    rewind(file);

    *data = (unsigned char*)malloc(*size);
    fread(*data, 1, *size, file);
    fclose(file);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned char *image_data = NULL;
    size_t image_size = 0;

    load_image(argv[1], &image_data, &image_size);

    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(image_data);
        return EXIT_FAILURE;
    }

    char query[1024];
    snprintf(query, sizeof(query), 
             "INSERT INTO %s (image) VALUES (%s)", TABLE,
             mysql_real_escape_string(conn, (char *) image_data, image_size));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(image_data);
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Image uploaded successfully.\n");

    free(image_data);
    mysql_close(conn);

    return EXIT_SUCCESS;
}


Before running this code, ensure that you have the MySQL C client library installed and properly linked during compilation. You can compile it using:


gcc -o image_to_db image_to_db.c $(mysql_config --cflags --libs)


Replace `testdb` with your actual database name, `images` with your table name, and make sure the column for storing binary data (e.g., BLOB) exists. Adjust the database connection details (`SERVER`, `USER`, `PASSWORD`) as needed.