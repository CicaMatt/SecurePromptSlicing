#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

void create_directory(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int main() {
    const char *html_content =
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Upload PDF</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h2>Upload a PDF File</h2>\n"
        "    <form action=\"/upload\" method=\"post\" enctype=\"multipart/form-data\">\n"
        "        <input type=\"file\" name=\"pdf_file\" accept=\"application/pdf\" required>\n"
        "        <button type=\"submit\">Upload</button>\n"
        "    </form>\n"
        "</body>\n"
        "</html>";

    const char *http_header =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Connection: close\r\n"
        "\r\n";

    create_directory(UPLOAD_DIR);

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        return EXIT_FAILURE;
    }

    if (listen(server_socket, 10) < 0) {
        perror("listen");
        close(server_socket);
        return EXIT_FAILURE;
    }

    printf("Server is running on http://localhost:8080\n");

    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);

        read(client_socket, buffer, BUFFER_SIZE);

        // Simple check to see if it's a GET request for the form
        if (strstr(buffer, "GET / ")) {
            write(client_socket, http_header, strlen(http_header));
            write(client_socket, html_content, strlen(html_content));
        } else if (strstr(buffer, "POST /upload")) {
            char *boundary = strstr(buffer, "boundary=");
            if (!boundary) {
                close(client_socket);
                continue;
            }
            boundary += 9;

            char file_name[BUFFER_SIZE];
            snprintf(file_name, BUFFER_SIZE, "%s/%d.pdf", UPLOAD_DIR, getpid());

            FILE *file = fopen(file_name, "wb");
            if (!file) {
                perror("fopen");
                close(client_socket);
                continue;
            }

            char *start_boundary = strstr(buffer, boundary);
            start_boundary += strlen(boundary) + 4; // Skip boundary and CRLF

            char *end_boundary = strstr(start_boundary, "--");
            char *content_disposition = strstr(start_boundary, "Content-Disposition: form-data;");
            if (!content_disposition || !end_boundary) {
                fclose(file);
                close(client_socket);
                continue;
            }

            content_disposition += 27; // Skip to the filename part
            char *filename_start = strstr(content_disposition, "filename=\"");
            if (!filename_start) {
                fclose(file);
                close(client_socket);
                continue;
            }
            filename_start += 10;

            char *filename_end = strchr(filename_start, '"');
            snprintf(file_name, BUFFER_SIZE, "%s/%.*s", UPLOAD_DIR, (int)(filename_end - filename_start), filename_start);

            start_boundary = strstr(end_boundary + 2, boundary);
            if (!start_boundary) {
                fclose(file);
                close(client_socket);
                continue;
            }

            char *file_data_start = end_boundary + 4; // Skip CRLF
            size_t file_size = (size_t)(start_boundary - file_data_start);

            fwrite(file_data_start, 1, file_size, file);
            fclose(file);

            write(client_socket, http_header, strlen(http_header));
            char *response_body = "<html><body><h2>File uploaded successfully!</h2></body></html>";
            write(client_socket, response_body, strlen(response_body));
        }

        close(client_socket);
    }

    close(server_socket);
    return 0;
}