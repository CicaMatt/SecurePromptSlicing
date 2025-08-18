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

    if (mysql_real_connect(con, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    FILE *file;
    char *filename;
    filename = argv[1];
    file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file.");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0L, SEEK_END);
    long img_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *buffer = (char *)malloc(img_size + 1);
    if (!buffer) {
        fclose(file);
        perror("Failed to allocate memory for buffer.");
        exit(EXIT_FAILURE);
    }

    fread(buffer, img_size, 1, file);
    fclose(file);

    char query[img_size + 256];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_real_escape_string(con, buffer, img_size));

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    free(buffer);
    mysql_close(con);

    return 0;
}