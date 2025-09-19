#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void check_mysql_error(MYSQL *conn) {
    if (mysql_errno(conn)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    const char *image_filename = argv[1];
    FILE *file = fopen(image_filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }
    
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    fclose(file);

    buffer[file_size] = '\0';

    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    const char query_template[] =
        "INSERT INTO images (image_data) VALUES (%s);";

    char query[1024 * 64];
    snprintf(query, sizeof(query), query_template, buffer);

    if (mysql_query(conn, query)) {
        check_mysql_error(conn);
    } else {
        printf("Image inserted successfully.\n");
    }

    mysql_close(conn);
    free(buffer);
    
    return 0;
}
