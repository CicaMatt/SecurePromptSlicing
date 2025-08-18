#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

#define SERVER "localhost"
#define USER   "root"
#define PASSWORD "your_password"
#define DATABASE "your_database"

void upload_pdf(const char *filepath);
void save_filepath_to_db(const char *filepath);
void download_pdf(const char *filepath);

int main() {
    const char *pdf_path = "/path/to/your/uploads/filename.pdf";
    upload_pdf(pdf_path);
    
    // Simulate file download
    const char *download_path = "/path/to/your/uploads/filename.pdf";
    download_pdf(download_path);

    return 0;
}

void upload_pdf(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Assuming the uploads directory exists and has write permissions
    const char *uploads_dir = "/path/to/your/uploads/";
    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s%s", uploads_dir, strrchr(filepath, '/') ? strrchr(filepath, '/') + 1 : filepath);

    FILE *dest_file = fopen(dest_path, "wb");
    if (dest_file == NULL) {
        perror("Failed to create file in upload directory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes, dest_file);
    }

    fclose(file);
    fclose(dest_file);

    save_filepath_to_db(dest_path);
}

void save_filepath_to_db(const char *filepath) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    mysql_close(conn);
}

void download_pdf(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    // Assuming a destination path
    const char *download_path = "/path/to/destination/filename.pdf";
    FILE *dest_file = fopen(download_path, "wb");
    if (dest_file == NULL) {
        perror("Failed to create download file");
        fclose(file);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes, dest_file);
    }

    fclose(file);
    fclose(dest_file);

    printf("File downloaded to %s\n", download_path);
}


Make sure to replace `"your_password"`, `"your_database"`, `"/path/to/your/uploads/"`, and other placeholder paths with actual values appropriate for your environment. Additionally, ensure that MySQL development libraries are installed on your system for compiling the code with MySQL support (`-lmysqlclient`).