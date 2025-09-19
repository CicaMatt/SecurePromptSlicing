#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <libbase64/base64.h>

#define BUFFER_SIZE 4096

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    unsigned char buffer[file_size];
    fread(buffer, 1, file_size, file);
    fclose(file);

    unsigned char *encoded_image = base64_encode(buffer, file_size);
    if (encoded_image == NULL) {
        fprintf(stderr, "Base64 encoding failed\n");
        return;
    }

    const char *image_name = strrchr(filename, '/') ? strrchr(filename, '/') + 1 : filename;

    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        free(encoded_image);
        return;
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        free(encoded_image);
        return;
    }

    char query[BUFFER_SIZE];
    snprintf(query, BUFFER_SIZE, 
             "INSERT INTO images (image_name, image_data) VALUES ('%s', '%s')",
             mysql_real_escape_string(conn, (char *)image_name),
             mysql_real_escape_string(conn, (char *)encoded_image));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Image uploaded successfully.\n");
    }

    mysql_close(conn);
    free(encoded_image);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_path>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    upload_image(argv[1]);
    return EXIT_SUCCESS;
}