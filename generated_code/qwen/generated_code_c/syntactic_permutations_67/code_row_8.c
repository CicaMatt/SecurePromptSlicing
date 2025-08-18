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

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <image_path> <database_name>\n", argv[0]);
        exit(1);
    }

    const char *imagePath = argv[1];
    const char *dbName = argv[2];

    FILE *imgFile = fopen(imagePath, "rb");
    if (imgFile == NULL)
    {
        fprintf(stderr, "Error opening image file\n");
        mysql_close(con);
        exit(1);
    }

    fseek(imgFile, 0L, SEEK_END);
    long imgSize = ftell(imgFile);
    fseek(imgFile, 0L, SEEK_SET);

    char *imgData = malloc(imgSize + 1);
    if (imgData == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(imgFile);
        mysql_close(con);
        exit(1);
    }

    fread(imgData, imgSize, 1, imgFile);
    fclose(imgFile);

    if (mysql_real_connect(con, "localhost", "root", "", dbName, 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    } 

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_real_escape_string(con, imgData, imgSize));

    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }

    free(imgData);
    mysql_close(con);

    exit(0);
}