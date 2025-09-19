#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILE_SIZE 1024 * 1024 * 5 // 5MB max file size

int main() {
    FILE *file;
    char buffer[MAX_FILE_SIZE];
    size_t bytesRead;

    if (mkdir(UPLOADS_DIR, 0777) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        exit(EXIT_FAILURE);
    }

    printf("Content-Type: text/html\n\n");

    printf("<html><body>");
    printf("<form action=\"\" method=\"post\" enctype=\"multipart/form-data\">");
    printf("<label for=\"file\">Choose a PDF file:</label>");
    printf("<input type=\"file\" name=\"file\" id=\"file\" accept=\".pdf\"><br><br>");
    printf("<input type=\"submit\" value=\"Upload\">");
    printf("</form>");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        char *content_type = getenv("CONTENT_TYPE");
        if (content_type && strstr(content_type, "multipart/form-data")) {
            file = fopen(UPLOADS_DIR "uploaded_file.pdf", "wb");
            if (!file) {
                perror("Failed to open file for writing");
                printf("<p>Failed to upload file.</p>");
            } else {
                bytesRead = fread(buffer, 1, sizeof(buffer), stdin);
                if (bytesRead > 0) {
                    fwrite(buffer, 1, bytesRead, file);
                    fclose(file);
                    printf("<p>File uploaded successfully.</p>");
                } else {
                    perror("Failed to read file data");
                    printf("<p>Failed to upload file.</p>");
                }
            }
        } else {
            printf("<p>Invalid content type. Please upload a PDF file.</p>");
        }
    }

    printf("</body></html>");

    return 0;
}