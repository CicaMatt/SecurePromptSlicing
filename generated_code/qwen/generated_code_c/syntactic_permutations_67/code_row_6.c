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

    if (con == NULL) 
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    } 

    if (mysql_real_connect(con, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }

    FILE *file;
    char *buffer;
    long fileLen;

    file = fopen(argv[1], "rb");
    if (!file) 
    {
        fprintf(stderr, "Unable to open file %s", argv[1]);
        exit(1);
    }
    
    fseek(file, 0, SEEK_END);
    fileLen=ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer=(char *)malloc(fileLen+1);
    if (!buffer)
    {
        fprintf(stderr, "Memory error!");
        fclose(file);
        exit(1);
    }

    fread(buffer, fileLen, 1, file);
    fclose(file);

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_real_escape_string(con, buffer, fileLen));

    if (mysql_query(con, query))
    {
        finish_with_error(con);
    }

    free(buffer);
    mysql_close(con);
    exit(0);
}