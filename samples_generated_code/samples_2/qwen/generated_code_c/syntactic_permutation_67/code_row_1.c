#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "image_db"

void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);        
}

int main(int argc, char **argv) {
    MYSQL *con = mysql_init(NULL);

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *image_data = malloc(file_size);
    if (!image_data) {
        fprintf(stderr, "Failed to allocate memory\n");
        fclose(file);
        return 1;
    }

    fread(image_data, file_size, 1, file);
    fclose(file);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }  

    if (mysql_real_connect(con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images(data, size) VALUES(_binary '%s', %ld)", image_data, file_size);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    mysql_close(con);
    free(image_data);

    return 0;
}