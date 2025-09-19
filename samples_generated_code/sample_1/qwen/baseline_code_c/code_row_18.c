#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

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

    if (mysql_real_connect(con, "localhost", "user", "password", 
          "database_name", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }    

    const char *image_path = argv[1];
    FILE *fp = fopen(image_path, "rb");
    if (!fp) {
        fprintf(stderr, "Cannot open file %s\n", image_path);
        return EXIT_FAILURE;
    }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char *buffer = (char *)malloc(size);
    fread(buffer, sizeof(char), size, fp);
    fclose(fp);

    char query[1024];
    snprintf(query, sizeof(query),
        "INSERT INTO images(data) VALUES('%.*s')", 
        size, buffer);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    free(buffer);
    mysql_close(con);
    exit(0);
}