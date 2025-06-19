#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8080

struct data {
    char *username;
    char *message;
};

void *handle_request(void *arg) {
    struct data *data = (struct data *) arg;
    printf("Username: %s\n", data->username);
    printf("Message: %s\n", data->message);
    free(data);
}

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        perror("socket failed");

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        perror("setsockopt");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0)
        perror("bind failed");

    if (listen(server_fd, 3) < 0)
        perror("listen");

    while ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen))) {
        valread = read(new_socket, buffer, 1024);
        if (valread < 0)
            perror("read");

        struct data *data = malloc(sizeof(struct data));
        char *username = strtok(buffer, "&=");
        char *message = strtok(NULL, "&=");
        data->username = username;
        data->message = message;

        pthread_t thread;
        if (pthread_create(&thread, NULL, handle_request, (void *) data) != 0)
            perror("Failed to create thread");
        if (pthread_join(thread, NULL) != 0)
            perror("Failed to join thread");
    }

    return 0;
}