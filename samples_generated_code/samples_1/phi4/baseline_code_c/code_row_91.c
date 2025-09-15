#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <mysql/mysql.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "base64.h"

#define BUFFER_SIZE 8192

void upload_image(const char *image_path, MYSQL *conn);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <image_path> <db_host>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *image_path = argv[1];
    const char *db_host = argv[2];

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, db_host, "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    upload_image(image_path, conn);

    mysql_close(conn);
    return EXIT_SUCCESS;
}

void read_file_to_buffer(const char *file_path, unsigned char **buffer) {
    FILE *fp = fopen(file_path, "rb");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    *buffer = (unsigned char *)malloc(file_size + 1);
    if (!*buffer) {
        perror("malloc");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fread(*buffer, 1, file_size, fp);
    (*buffer)[file_size] = '\0';
    fclose(fp);
}

void upload_image(const char *image_path, MYSQL *conn) {
    unsigned char *image_data;
    read_file_to_buffer(image_path, &image_data);

    size_t data_len = strlen((const char *)image_data);
    char *base64_encoded = base64_encode(image_data, data_len);

    const char *query = "INSERT INTO images (name, image) VALUES (%s, %s)";
    char insert_query[1024];
    snprintf(insert_query, sizeof(insert_query), query, image_path, base64_encoded);

    if (mysql_query(conn, insert_query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(base64_encoded);
        free(image_data);
        return;
    }

    printf("Image uploaded successfully.\n");

    free(base64_encoded);
    free(image_data);
}
