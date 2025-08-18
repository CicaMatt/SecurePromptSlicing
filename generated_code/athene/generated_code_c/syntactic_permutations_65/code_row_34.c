#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int n;
    
    while ((n = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"") != NULL) {
            const char *start = strstr(buffer, "filename=\"") + strlen("filename=\"");
            const char *end = strchr(start, '"');
            int filename_len = end - start;
            char filename[filename_len + 1];
            strncpy(filename, start, filename_len);
            filename[filename_len] = '\0';

            FILE *file = fopen(strcat(UPLOAD_DIR, filename), "wb");
            if (file == NULL) {
                close(client_socket);
                return;
            }

            const char *data_start = strstr(buffer, "\r\n\r\n") + 4;
            fwrite(data_start, 1, n - (data_start - buffer), file);

            while ((n = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
                if (strstr(buffer, "--") != NULL) break;
                fwrite(buffer, 1, n, file);
            }

            fclose(file);
        }
    }
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (access(UPLOAD_DIR, F_OK) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        return 1;
    }

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}