#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <mysql/mysql.h>

// MySQL Connection Information
char *server = "127.0.0.1";
char *user = "root";
char *password = "";
char *database = "image_uploader";

// MySQL Initialization Functions
int init_connection();
void close_connection(MYSQL *con);

// Image Upload Functions
int upload_image(FILE *fp, char *file_name);
int insert_image_data(char *file_name, char *file_path);

// Main Execution Loop
int main() {
    // Initialize MySQL Connection
    MYSQL *con = init_connection();
    if (con == NULL) {
        printf("MySQL Initialization Error\n");
        exit(1);
    }

    // File Upload Prompt
    char file_path[256];
    char file_name[256];
    FILE *fp;
    int upload_status = 0;

    printf("Enter the path of the image you want to upload: ");
    fgets(file_path, sizeof(file_path), stdin);
    strtok(file_path, "\n");

    // Upload Image Function Call
    upload_status = upload_image(fp, file_name);
    if (upload_status == 0) {
        printf("Image upload failed\n");
        close_connection(con);
        return -1;
    }

    // Insert Image Data into Database Function Call
    insert_image_data(file_name, file_path);

    // Close MySQL Connection
    close_connection(con);

    return 0;
}

// Initialize MySQL Connection Function
int init_connection() {
    MYSQL *con = mysql_init(NULL);

    if (!mysql_real_connect(con, server, user, password, database, 0, NULL, 0)) {
        printf("MySQL Connection Error: %s\n", mysql_error(con));
        return -1;
    }
    return con;
}

// Close MySQL Connection Function
void close_connection(MYSQL *con) {
    if (con != NULL) {
        mysql_close(con);
    }
}

// Upload Image Function
int upload_image(FILE *fp, char *file_name) {
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Image Opening Error\n");
        return 0;
    }

    // Read Image File and Convert to Base64 String
    char *image = malloc(sizeof(char) * 1024);
    while ((fgets(image, 1023, fp)) != NULL) {
        printf("%s", image);
    }
    fclose(fp);

    // Insert Image Data into Database Function Call
    insert_image_data(file_name, image);
}

// Insert Image Data into Database Function
int insert_image_data(char *file_name, char *image) {
    MYSQL *con = init_connection();

    // MySQL Query String
    char query[256];
    sprintf(query, "INSERT INTO images (image_path, image_name, image) VALUES ('%s', '%s', '%s')", file_name, image);

    if (mysql_query(con, query)) {
        printf("MySQL Insertion Error: %s\n", mysql_error(con));
        return -1;
    } else {
        printf("Image inserted successfully\n");
        return 0;
    }
}