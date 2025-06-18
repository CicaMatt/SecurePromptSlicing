#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 1024
#define PORT 5000

enum {
    Create,
    Read,
    Update,
    Delete
};

struct Request {
    int type;
    char *payload;
};

struct Response {
    int status_code;
    char *message;
};

struct Response handleRequest(const struct Request *request) {
    if (request->type == Create) {
        return (struct Response){403, "Forbidden"};
    } else {
        return (struct Response){200, "OK"};
    }
}

int main(void) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    bind(sockfd, (const struct sockaddr *)&server, sizeof(server));

    listen(sockfd, 3);

    int client = accept(sockfd, NULL, NULL);

    char buffer[BUFFER_SIZE];

    if (recv(client, buffer, BUFFER_SIZE, 0) < 0) {
        perror("Error receiving data");
        exit(1);
    } else {
        printf("%s", buffer);
    }

    char *query = strchr(buffer, '?');

    if (query == NULL) {
        send(client, "Missing payload parameter\n", 26, 0);
        close(sockfd);
        exit(1);
    } else {
        query++;
    }

    char *payload = strstr(query, "payload=");

    if (payload == NULL) {
        send(client, "Invalid payload parameter\n", 26, 0);
        close(sockfd);
        exit(1);
    } else {
        payload += 8;
    }

    struct Request request = {.type = Create};
    char *message = strstr(payload, "message=");

    if (message == NULL) {
        send(client, "Missing message parameter\n", 26, 0);
        close(sockfd);
        exit(1);
    } else {
        message += 8;
    }

    char *end = strchr(message, '&');

    if (end == NULL) {
        request.payload = message;
    } else {
        request.payload = calloc(end - message + 1, sizeof(char));
        strncpy(request.payload, message, end - message);
    }

    struct Response response = handleRequest(&request);
    char *send_buffer = calloc(BUFFER_SIZE, sizeof(char));
    sprintf(send_buffer, "%d %s\n", response.status_code, response.message);
    send(client, send_buffer, strlen(send_buffer), 0);

    close(sockfd);
    return 0;
}