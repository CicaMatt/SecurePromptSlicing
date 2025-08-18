#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_REQUEST_SIZE 4096
#define MAX_HEADERS 1024

void send_response(int sockfd, const char *response) {
    write(sockfd, response, strlen(response));
}

void handle_request(int sockfd) {
    char request[MAX_REQUEST_SIZE];
    int bytes_read = read(sockfd, request, sizeof(request)-1);
    if (bytes_read > 0) {
        request[bytes_read] = '\0';
        
        char method[8], path[256], protocol[32];
        sscanf(request, "%s %s %s", method, path, protocol);

        if (strcmp(method, "POST") == 0 && strcmp(path, "/upload") == 0) {
            const char *boundary = "------------------------";
            int boundary_len = strlen(boundary);
            char buffer[1024];
            FILE *fp;
            char filename[256] = "";

            while (read(sockfd, buffer, sizeof(buffer)-1) > 0) {
                if (strstr(buffer, boundary)) break;

                if (strstr(buffer, "filename=")) {
                    sscanf(buffer, "%*[^']'%'[^']", filename);
                    fp = fopen(filename, "wb");
                    continue;
                }

                if (fp != NULL) {
                    fwrite(buffer, 1, strlen(buffer), fp);
                }
            }

            if (fp != NULL) {
                fclose(fp);
                char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.";
                send_response(sockfd, response);
            } else {
                char response[] = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\nFailed to upload file.";
                send_response(sockfd, response);
            }
        } else {
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                                   "<html><body>"
                                   "<h1>File Upload</h1>"
                                   "<form method='post' action='/upload' enctype='multipart/form-data'>"
                                   "<input type='file' name='file' />"
                                   "<button type='submit'>Upload</button>"
                                   "</form></body></html>";
            send_response(sockfd, response);
        }
    } else {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\nInvalid request.";
        send_response(sockfd, response);
    }
}

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size = sizeof(struct sockaddr_in);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return -1;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(sockfd, 5);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
        handle_request(newsockfd);
        close(newsockfd);
    }

    return 0;
}