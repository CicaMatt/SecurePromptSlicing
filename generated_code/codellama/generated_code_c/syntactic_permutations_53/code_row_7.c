#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <errno.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netdb.h>

#include <netinet/in.h>



typedef struct {

    const char *username;

    const char *password;

} user_t;



int authenticate(const char *username, const char *password);

void redirect_user();

void redirect_admin();

void render_not_found();

void handle_request(int client_socket);



user_t users[] = {

    {"john", "secret1"},

    {"jane", "secret2"},

    {"bob", "secret3"},

};



int main() {

    int server_fd, client_socket;

    struct sockaddr_in address;

    int opt = 1;

    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {

        perror("socket failed");

        exit(EXIT_FAILURE);

    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {

        perror("setsockopt");

        exit(EXIT_FAILURE);

    }

    address.sin_family = AF_INET;

    address.sin_addr.s_addr = INADDR_ANY;

    address.sin_port = htons(8080);



    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {

        perror("bind failed");

        exit(EXIT_FAILURE);

    }

    if (listen(server_fd, 3) < 0) {

        perror("listen");

        exit(EXIT_FAILURE);

    }



    while ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {

        handle_request(client_socket);

    }

    return 0;

}



void redirect_user() {

    printf("HTTP/1.1 302 Found\r\n");

    printf("Location: /user\r\n");

    printf("\r\n");

}



void redirect_admin() {

    printf("HTTP/1.1 302 Found\r\n");

    printf("Location: /admin\r\n");

    printf("\r\n");

}



void render_not_found() {

    printf("HTTP/1.1 404 Not Found\r\n");

    printf("Content-Type: text/plain\r\n");

    printf("\r\n");

    printf("Not found\r\n");

}



int authenticate(const char *username, const char *password) {

    for (size_t i = 0; i < sizeof(users) / sizeof(user_t); i++) {

        if (!strcmp(username, users[i].username) && !strcmp(password, users[i].password))

            return 1;

    }

    return 0;

}



void handle_request(int client_socket) {

    char *line = NULL;

    size_t len = 0;

    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {

        if (strstr(line, "Authorization: Basic")) {

            int auth = 0;

            char *token = strtok(line, " ");

            token = strtok(NULL, "\n");



            if (authenticate(token)) {

                redirect_user();

                return;

            } else {

                render_not_found();

                return;

            }

        }

    }

}
