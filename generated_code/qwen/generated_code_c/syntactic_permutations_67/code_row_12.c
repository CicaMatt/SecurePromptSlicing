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

    if (con == NULL) 
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    } 

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    FILE *fp = fopen(file_path, "rb");
    if (!fp) 
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    char *image_data = malloc(size + 1);
    if (!image_data) 
    {
        perror("Failed to allocate memory");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fread(image_data, 1, size, fp);
    fclose(fp);

    if (mysql_real_connect(con, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    } 

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images (data) VALUES (%s)", mysql_real_escape_string(con, image_data, size));

    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }

    free(image_data);
    mysql_close(con);

    return 0;
}


Make sure to replace `"username"`, `"password"`, and `"database_name"` with your MySQL credentials and database name. Also, ensure that the `images` table exists in your database with a column named `data` of type `BLOB`.