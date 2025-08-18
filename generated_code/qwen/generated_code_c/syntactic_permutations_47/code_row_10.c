#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_file(int client_socket, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        char response[] = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile not found";
        send(client_socket, response, strlen(response), 0);
        return;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    char *buffer = malloc(file_size + 1);
    fread(buffer, file_size, 1, fp);
    fclose(fp);

    char response_header[512];
    sprintf(response_header, "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\nConnection: close\r\n\r\n", file_size);

    send(client_socket, response_header, strlen(response_header), 0);
    send(client_socket, buffer, file_size, 0);
    free(buffer);
}

void handle_request(int client_socket) {
    char request[BUFFER_SIZE];
    recv(client_socket, request, sizeof(request), 0);

    const char *get_token = "GET /images/";
    if (strncmp(request, get_token, strlen(get_token)) == 0) {
        char filename[256] = "images/";
        for (int i = strlen(get_token); request[i] != ' '; ++i) {
            filename[strlen("images/") + i - strlen(get_token)] = request[i];
        }
        send_file(client_socket, filename);
    } else {
        char response[] = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nInvalid request";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_len = sizeof(client_address);

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    listen(server_socket, 5);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_request(client_socket);
    }

    close(server_socket);
    return 0;
}