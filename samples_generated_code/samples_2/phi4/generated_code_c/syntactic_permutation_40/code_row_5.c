#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = { .username = "user123", .email = "user@example.com", .ssn = "123-45-6789" };

void info() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Info Page</h1>");
    printf("<p>Username: %s</p>", session.username);
    printf("<p>Email: %s</p>", session.email);

    char last4ssn[5] = {0};
    strncpy(last4ssn, session.ssn + 6, 4); // Extract the last 4 digits of SSN
    printf("<p>Last 4 digits of SSN: %s</p>", last4ssin);
    printf("</body></html>");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);

    // Simple web server setup using basic socket programming
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);

        if (strncmp(buffer, "GET /info HTTP/1.1", 17) == 0) {
            info();
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body><h1>404 Not Found</h1></body></html>");
        }

        write(new_socket, buffer, strlen(buffer));
        close(new_socket);
    }
    
    close(server_fd);

    return 0;
}