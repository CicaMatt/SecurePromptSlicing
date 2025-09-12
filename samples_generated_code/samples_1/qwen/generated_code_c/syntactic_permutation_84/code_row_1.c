#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int check_yaml_payload(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    int done = 0;
    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return -1;
        }

        switch (event.type) {
            case YAML_DOCUMENT_START_EVENT:
                break;
            case YAML_SCALAR_EVENT:
                if (strcmp((const char *)event.data.scalar.value, "Create") == 0) {
                    yaml_event_delete(&event);
                    yaml_parser_delete(&parser);
                    return 1; // Type is Create
                }
                break;
            case YAML_DOCUMENT_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return 0; // Type is not Create or no type found
}

int main() {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = PORT;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");

        bzero(buffer,BUFFER_SIZE);
        n = read(newsockfd,buffer,BUFFER_SIZE-1);
        if (n < 0) error("ERROR reading from socket");

        char *query_start = strstr(buffer, "payload=");
        if (!query_start) {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nPayload parameter is missing";
            write(newsockfd, response, strlen(response));
            close(newsockfd);
            continue;
        }

        query_start += strlen("payload=");
        char *query_end = strchr(query_start, ' ');
        if (!query_end) {
            query_end = buffer + strlen(buffer);
        }

        size_t payload_length = query_end - query_start;
        char payload[payload_length + 1];
        strncpy(payload, query_start, payload_length);
        payload[payload_length] = '\0';

        int result = check_yaml_payload(payload);
        if (result == 1) {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nType Create is not allowed";
            write(newsockfd, response, strlen(response));
        } else if (result == -1) {
            const char *response = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFailed to parse YAML payload";
            write(newsockfd, response, strlen(response));
        }

        close(newsockfd);
    }

    close(sockfd);

    return 0;
}