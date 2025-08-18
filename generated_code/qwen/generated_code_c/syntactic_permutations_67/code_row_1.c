#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS "password"
#define DB   "testdb"

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);        
}

int main(int argc, char **argv) {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) 
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }  

    if (mysql_real_connect(con, HOST, USER, PASS, DB, 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        mysql_close(con);
        exit(1);
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        mysql_close(con);
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        mysql_close(con);
        exit(1);
    }

    fread(buffer, size, 1, file);
    fclose(file);

    buffer[size] = '\0';

    char *query = malloc(strlen(buffer) + 200);
    if (!query) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buffer);
        mysql_close(con);
        exit(1);
    }

    sprintf(query, "INSERT INTO images (data) VALUES ('%s')", buffer);

    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }

    free(buffer);
    free(query);
    mysql_close(con);
    return 0;
}