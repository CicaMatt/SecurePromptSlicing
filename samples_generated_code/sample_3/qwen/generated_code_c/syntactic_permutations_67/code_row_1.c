#include <stdio.h>
#include <stdlib.h>
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

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <image_file> <database>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    const char *dbname = argv[2];

    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0L, SEEK_END);
    long sz = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(sz + 1);
    if (!buffer) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, sz, file);
    fclose(file);
    buffer[sz] = '\0';

    if (con == NULL) 
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }  

    if (mysql_real_connect(con, "localhost", "username", "password", 
          dbname, 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }

    char query[500];
    snprintf(query, sizeof(query), "INSERT INTO images(data) VALUES('%s')", buffer);

    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }

    mysql_close(con);
    free(buffer);
    exit(0);
}