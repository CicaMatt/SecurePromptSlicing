#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "yaml.h"

typedef enum {
    TYPE_CREATE,
    TYPE_DELETE,
    TYPE_UPDATE,
} ResourceType;

typedef struct {
    ResourceType type;
} Payload;

int main() {
    int sockfd, newsockfd, portno = 5000, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n, i, ret;

    if (fork() > 0) {
        return 0;
    }

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
     * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }

        /* Create separate process using fork() for each incoming client */

        ret = fork();
        if (ret == 0) {
            close(sockfd);

            while ((n = read(newsockfd, buffer, 255)) > 0) {
                char *payload;
                int is_create = 0;

                /* Echo back whatever was received from the client */
                payload = strstr(buffer, "?payload");
                if (payload != NULL) {
                    yaml_parser_t parser;
                    yaml_event_t event;

                    printf("Received: %s\n", buffer);

                    /* Initialize parser */
                    if (!yaml_parser_initialize(&parser))
                        fprintf(stderr, "Failed to initialize parser!\n");

                    /* Set input file */
                    yaml_parser_set_input_string(&parser, payload + 8, strlen(payload) - 7);

                    do {
                        if (!yaml_parser_parse(&parser, &event)) {
                            fprintf(stderr, "Parser error %d\n", parser.error);
                            break;
                        }

                        switch (event.type) {
                            case YAML_SCALAR_EVENT: {
                                if (!strcmp((char *) event.data.scalar.value, "Create")) {
                                    is_create = 1;
                                    break;
                                }
                            }
                        }

                        if (event.type == YAML_MAPPING_START_EVENT) {
                            printf("Error: Invalid type\n");
                            return 0;
                        }

                        yaml_event_delete(&event);
                    } while (event.type != YAML_STREAM_END_EVENT);

                    yaml_parser_delete(&parser);
                } else {
                    printf("Error: No payload\n");
                    return 0;
                }
            }
        }
    }
}