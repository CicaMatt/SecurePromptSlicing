#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

// MySQL database credentials
#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "image_gallery"

// Image upload function
void upload_image()
{
    // Get image file path from user input
    char image_path[256];
    printf("Enter the image file path: ");
    scanf("%s", &image_path);

    // Open and read image file
    int fd = open(image_path, O_RDONLY);
    struct stat st;
    fstat(fd, &st);
    char *buffer = (char *)malloc(sizeof(char) * (st.st_size + 1));
    read(fd, buffer, st.st_size);
    close(fd);

    // Convert image file to base64 string
    int length = strlen(buffer);
    char *base64_string = (char *)malloc(sizeof(char) * (length * 2));
    bzero(base64_string, sizeof(base64_string));
    int i = 0;
    while (i < length)
    {
        sprintf(base64_string + (i * 2), "%02x", buffer[i]);
        i++;
    }

    // Connect to MySQL database and insert image details into 'images' table
    MYSQL mysql;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0))
    {
        printf("Failed to connect to MySQL database\n");
        return;
    }

    char query[512];
    bzero(query, sizeof(query));
    sprintf(query, "INSERT INTO images (name, base64) VALUES ('%s', '%s')", image_path + 9, base64_string);
    if (mysql_query(&mysql, query))
        printf("Failed to insert image details into MySQL database\n");

    // Close MySQL connection
    mysql_close(&mysql);

    // Free memory
    free(buffer);
    free(base64_string);
}

int main()
{
    upload_image();
    return 0;
}