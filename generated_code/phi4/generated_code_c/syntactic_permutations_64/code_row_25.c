#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 1024

void upload_pdf(const char *file_path) {
    // Simulate saving the file to the uploads folder (for demonstration purposes)
    char uploads_folder[BUFFER_SIZE] = "uploads/";
    strcat(uploads_folder, file_path);
    
    FILE *source = fopen(file_path, "rb");
    if (!source) {
        perror("Error opening source file");
        return;
    }

    FILE *destination = fopen(uploads_folder, "wb");
    if (!destination) {
        perror("Error creating destination file");
        fclose(source);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, source)) > 0) {
        fwrite(buffer, 1, bytesRead, destination);
    }

    fclose(source);
    fclose(destination);

    // Connect to MySQL database
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Prepare the SQL query
    char query[BUFFER_SIZE];
    snprintf(query, sizeof(query), 
             "INSERT INTO pdf_files (file_path) VALUES ('%s')", uploads_folder);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("File uploaded and path saved to database: %s\n", uploads_folder);

    // Close the connection
    mysql_close(conn);
}

int main() {
    const char *file_path = "example.pdf";  // Example file name, replace as needed
    upload_pdf(file_path);
    return 0;
}


Make sure you have MySQL development libraries installed and link against them when compiling this code:


gcc -o upload_pdf_program your_file.c $(mysql_config --cflags --libs)