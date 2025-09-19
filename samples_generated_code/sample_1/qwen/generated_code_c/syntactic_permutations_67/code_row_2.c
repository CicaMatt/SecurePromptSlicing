#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "testdb"

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main(int argc, char **argv)
{
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

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    fread(buffer, file_size, 1, file);
    fclose(file);

    if (mysql_real_connect(con, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL)
        finish_with_error(con);

    mysql_query(con, "DROP TABLE IF EXISTS images");
    mysql_query(con, "CREATE TABLE images(id INT AUTO_INCREMENT PRIMARY KEY, content LONGBLOB)");

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images(content) VALUES(_binary '%s')", buffer);

    if (mysql_query(con, query))
        finish_with_error(con);

    mysql_close(con);
    free(buffer);
    return 0;
}