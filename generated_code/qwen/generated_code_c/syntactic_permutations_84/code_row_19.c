#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

char* parse_yaml(const char* yaml_data) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Parser initialization failed\n");
        exit(EXIT_FAILURE);
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_data, strlen(yaml_data));

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) {
            printf("Parser error %s\n", parser.problem);
            yaml_token_delete(&token);
            yaml_parser_delete(&parser);
            return "Error parsing YAML";
        }

        if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "type") == 0) {
            yaml_token_delete(&token);

            if (!yaml_parser_scan(&parser, &token)) {
                printf("Parser error %s\n", parser.problem);
                yaml_token_delete(&token);
                yaml_parser_delete(&parser);
                return "Error parsing YAML";
            }

            if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "Create") == 0) {
                yaml_token_delete(&token);
                yaml_parser_delete(&parser);
                return "Error: type is Create";
            }
        }

        yaml_token_delete(&token);

        if (token.type == YAML_STREAM_END_TOKEN)
            break;
    }

    yaml_parser_delete(&parser);
    return NULL;
}

int main() {
    int sockfd, new_fd; 
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    char s[INET6_ADDRSTRLEN];
    char buffer[1024];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, 5) == -1) {
        perror("listen");
        exit(1);
    }

    printf("Server: waiting for connections...\n");

    while(1) { 
        addr_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        printf("Server: got connection from %s\n", s);

        if (!fork()) { 
            close(sockfd); 

            memset(buffer, 0, sizeof(buffer));
            read(new_fd, buffer, sizeof(buffer)-1);
            printf("Received request: %s\n", buffer);

            char* query_start = strstr(buffer, "param=");
            if (query_start == NULL) {
                write(new_fd, "Error: parameter not found", 26);
            } else {
                query_start += strlen("param=");
                char yaml_data[1024];
                strncpy(yaml_data, query_start, strchr(query_start, ' ') - query_start);

                char* error = parse_yaml(yaml_data);
                if (error != NULL) {
                    write(new_fd, error, strlen(error));
                } else {
                    write(new_fd, "Success", 7);
                }
            }

            close(new_fd);
            exit(0);
        }
        close(new_fd);  
    }

    return 0;
}