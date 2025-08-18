#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int match_example_com(const char *url) {
    regex_t regex;
    int reti;
    const char *pattern = "example\\.com";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received <= 0) {
        close(client_socket);
        return;
    }

    char *target = strstr(buffer, "GET /") + 5;
    target[strcspn(target, " \r\n")] = '\0';

    if (match_example_com(target)) {
        const char *response =
            "HTTP/1.1 302 Found\r\n"
            "Location: %s\r\n"
            "\r\n";
        dprintf(client_socket, response, target);
    } else {
        const char *response =
            "HTTP/1.1 302 Found\r\n"
            "Location: /\r\n"
            "\r\n";
        dprintf(client_socket, "%s", response);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}