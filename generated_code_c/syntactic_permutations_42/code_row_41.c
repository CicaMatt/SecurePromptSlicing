// import necessary dependencies
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// structure to store user data
typedef struct {
    char *username;
    char *email;
    char *ssn;
} UserData;

// function to handle /info route
void info(UserData user) {
    printf("Username: %s\nEmail: %s\nSSN: %s\n", user.username, user.email, user.ssn);
}

int main() {
    // create a socket
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    char buffer[1024] = {0};
    read(new_socket, buffer, 1024);

    // parse the http request to get the route
    char *route = strtok(buffer, " \n");
    route = strtok(NULL, " \n");

    // call the appropriate function based on the route
    if (strcmp("/info", route) == 0) {
        UserData user;
        user.username = "john.doe";
        user.email = "johndoe@example.com";
        user.ssn = "123-45-6789";
        info(user);
    }

    char *response = "<!DOCTYPE html>\n<html lang=\"en\">\n<body>\nHello from web server!\n</body>\n</html>";

    write(new_socket, response, strlen(response));
    return 0;
}