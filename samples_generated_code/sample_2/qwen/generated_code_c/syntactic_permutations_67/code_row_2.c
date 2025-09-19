#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main(int argc, char **argv) 
{
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    long sz = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *image_data = malloc(sz + 1);
    if (!image_data) {
        perror("Memory allocation failed");
        fclose(file);
        exit(1);
    }

    fread(image_data, 1, sz, file);
    fclose(file);

    if (mysql_real_connect(con, "localhost", "user", "password", 
                           "database_name", 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%c%s%c)", '\'', image_data, '\'');

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    mysql_close(con);
    free(image_data);
    return 0;
}