#include <stdio.h>
#include <string.h>

#define PORT 8080

void send_response(FILE *fp) {
    fprintf(fp, "HTTP/1.1 200 OK\r\n");
    fprintf(fp, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(fp, "Connection: close\r\n");
    fprintf(fp, "\r\n");
    fprintf(fp, "<!DOCTYPE html><html><body><h1>Hello, World!</h1></body></html>");
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        return -1;
    }

    printf("Server is running on port %d\n", PORT);

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            return -1;
        }

        FILE *fp = fdopen(new_socket, "r+");
        if (!fp) {
            perror("fdopen failed");
            close(new_socket);
            continue;
        }

        fgets(buffer, sizeof(buffer), fp);

        send_response(fp);

        fclose(fp);
    }

    close(server_fd);
    return 0;
}