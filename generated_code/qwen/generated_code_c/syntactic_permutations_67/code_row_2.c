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
    long fileLen;

    // Open the image file in binary mode
    file = fopen("path_to_image.jpg", "rb");
    if (!file)
    {
        fprintf(stderr, "Unable to open file!");
        mysql_close(con);
        exit(1);
    }
    
    // Get file length
    fseek(file, 0, SEEK_END);
    fileLen=ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the image data
    char *buffer=(char *)malloc(fileLen+1);
    if (!buffer)
    {
        fprintf(stderr, "Memory error!");
        fclose(file);
        mysql_close(con);
        exit(1);
    }

    // Read file contents into buffer
    fread(buffer, fileLen, 1, file);
    fclose(file);

    // Prepare SQL query to insert the image data
    char *query = malloc(30 + fileLen * 2); // Allocate memory for query string
    if (!query)
    {
        fprintf(stderr, "Memory error!");
        free(buffer);
        mysql_close(con);
        exit(1);
    }

    sprintf(query, "INSERT INTO images (image_data) VALUES (X'%.*s')", (int)fileLen * 2, buffer);

    // Convert binary data to hexadecimal for SQL insertion
    char hex[fileLen*2 + 1];
    int i;
    for(i = 0; i < fileLen; i++)
        sprintf(&hex[i*2], "%02X", (unsigned char)buffer[i]);

    free(buffer);
    free(query);

    query = malloc(30 + strlen(hex));
    if (!query)
    {
        fprintf(stderr, "Memory error!");
        mysql_close(con);
        exit(1);
    }

    sprintf(query, "INSERT INTO images (image_data) VALUES ('%s')", hex);

    // Execute SQL query
    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }
    
    free(query);
    mysql_close(con);
    exit(0);        
}