#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request) {
    if (strstr(request, "GET / ") != NULL) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Simple File Upload Server</h1>");
        printf("<form action=\"/upload\" method=\"post\" enctype=\"multipart/form-data\">");
        printf("<input type=\"file\" name=\"file\"><br>");
        printf("<input type=\"submit\" value=\"Upload\">");
        printf("</form>");
        printf("</body></html>\n");
    } else if (strstr(request, "POST /upload") != NULL) {
        char *boundary = strstr(request, "boundary=") + 9;
        boundary[strcspn(boundary, "\r\n")] = '\0';

        const char *header_end = strstr(request, "\r\n\r\n");
        header_end += 4;

        const char *body_start = strstr(header_end, "--" + strlen("--") + strlen(boundary) + 2);
        if (body_start != NULL) {
            body_start += strlen("--") + strlen(boundary) + 3;
            const char *file_data_start = strstr(body_start, "\r\n\r\n");
            file_data_start += 4;

            const char *file_data_end = strstr(file_data_start, "\r\n--" + strlen("\r\n--"));
            if (file_data_end == NULL) {
                file_data_end = strstr(file_data_start, "\r\n") + 2;
            }

            size_t file_size = file_data_end - file_data_start;
            char *file_data = malloc(file_size);
            strncpy(file_data, file_data_start, file_size);

            FILE *uploaded_file = fopen("uploaded.txt", "wb");
            if (uploaded_file != NULL) {
                fwrite(file_data, 1, file_size, uploaded_file);
                fclose(uploaded_file);
                printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
                printf("<html><body>");
                printf("<h1>File Uploaded Successfully!</h1>");
                printf("</body></html>\n");
            } else {
                printf("HTTP/1.1 500 Internal Server Error\nContent-Type: text/html\n\n");
                printf("<html><body>");
                printf("<h1>Error uploading file</h1>");
                printf("</body></html>\n");
            }
        } else {
            printf("HTTP/1.1 400 Bad Request\nContent-Type: text/html\n\n");
            printf("<html><body>");
            printf("<h1>Bad request</h1>");
            printf("</body></html>\n");
        }

        free(file_data);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Not found</h1>");
        printf("</body></html>\n");
    }
}

void start_server(int port) {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1) {
        perror("listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server started on port %d\n", port);

    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
        if (client_socket < 0) {
            perror("accept failed");
            continue;
        }

        char buffer[BUFFER_SIZE];
        int bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            handle_request(buffer);
        }
        close(client_socket);
    }

    close(server_socket);
}

int main(int argc, char *argv[]) {
    int port = 8080;
    if (argc == 2) {
        port = atoi(argv[1]);
    }
    start_server(port);
    return 0;
}