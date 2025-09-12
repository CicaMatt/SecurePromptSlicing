#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libyaml/yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int parse_yaml(const char* yaml_data, char** type) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Parser initialization failed\n");
        return 0;
    }
    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_data, strlen(yaml_data));

    do {
        if (!yaml_parser_parse(&parser, &token)) {
            fprintf(stderr, "Parse error: %s\n", parser.problem);
            yaml_token_delete(&token);
            yaml_parser_delete(&parser);
            return 0;
        }
        if (token.type == YAML_SCALAR_TOKEN && strcmp((const char*)token.data.scalar.value, "type") == 0) {
            yaml_token_t next_token;
            if (!yaml_parser_parse(&parser, &next_token)) {
                fprintf(stderr, "Parse error: %s\n", parser.problem);
                yaml_token_delete(&token);
                yaml_token_delete(&next_token);
                yaml_parser_delete(&parser);
                return 0;
            }
            *type = strdup((const char*)next_token.data.scalar.value);
            yaml_token_delete(&next_token);
        }
        yaml_token_delete(&token);
    } while (token.type != YAML_STREAM_END_TOKEN);

    yaml_parser_delete(&parser);
    return 1;
}

int main() {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = PORT;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    while(1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) error("ERROR on accept");
        bzero(buffer,BUFFER_SIZE);
        int n = read(newsockfd,buffer,BUFFER_SIZE-1);
        if (n < 0) error("ERROR reading from socket");

        char* payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 25\r\nContent-Type: text/plain\r\n\r\nError: No payload parameter";
            write(newsockfd, response, strlen(response));
            close(newsockfd);
            continue;
        }

        payload_start += strlen("payload=");
        char* end = strchr(payload_start, ' ');
        if (end) *end = '\0';

        char* type = NULL;
        int success = parse_yaml(payload_start, &type);

        const char* response;
        if (!success || strcmp(type, "Create") == 0) {
            response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 23\r\nContent-Type: text/plain\r\n\r\nError: Invalid payload type";
        } else {
            response = "HTTP/1.1 200 OK\r\nContent-Length: 18\r\nContent-Type: text/plain\r\n\r\nRequest processed successfully";
        }

        write(newsockfd, response, strlen(response));
        close(newsockfd);
        free(type);
    }
    close(sockfd);

    return 0;
}