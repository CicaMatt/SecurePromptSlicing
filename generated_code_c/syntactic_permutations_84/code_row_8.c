#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <yaml.h>

int running = 1;
void sig_handler(int signo) {
    if (signo == SIGINT || signo == SIGTERM || signo == SIGKILL) {
        running = 0;
    }
}

struct sockaddr_in addr, cli;
socklen_t clilen;
int serv_sock;
void *process_request(void *arg);

char payload[1024];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGKILL, sig_handler);
    int yes = 1;
    struct sockaddr_in serv_addr;
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    listen(serv_sock, 10);
    clilen = sizeof(cli);
    while (running) {
        int connfd = accept(serv_sock, (struct sockaddr*) &cli, &clilen);
        pthread_t thread;
        if (pthread_create(&thread, NULL, process_request, (void *)(long)connfd) != 0) {
            perror("Failed to create new thread\n");
            close(connfd);
            continue;
        }
    }
    shutdown(serv_sock, SHUT_RDWR);
    return 0;
}

void *process_request(void *arg) {
    int connfd = (int)(long)arg;
    char buffer[1024];
    bzero(buffer, sizeof(buffer));
    read(connfd, buffer, sizeof(buffer));
    if (strlen(buffer)) {
        int payload_length = 0;
        char *payload = NULL;
        sscanf(buffer, "GET /?payload=%s HTTP/1.1\n", payload);
        while ((payload[payload_length++]) != '\0');
        pthread_mutex_lock(&mutex);
        yaml_parser_t parser;
        yaml_parser_initialize(&parser);
        yaml_parser_set_input_string(&parser, payload, payload_length);

        yaml_document_t document;
        if (!yaml_parser_load(&parser, &document)) {
            yaml_node_t *root = yaml_document_get_root_node(&document);
            yaml_tag_directive_t *start = document.start_tag_directives.start;
            if (strcmp(start->handle, "!") == 0 && strcmp(start->prefix, "Create") == 0) {
                printf("Invalid Request\n");
                yaml_document_delete(&document);
                write(connfd, "Error", sizeof("Error"));
            } else {
                printf("Valid request received\n");
                char *output = malloc(sizeof(char) * 1024);
                sprintf(output, "Received: %s\n", payload);
                write(connfd, output, strlen(output));
            }
        } else {
            printf("Invalid request received\n");
            write(connfd, "Error", sizeof("Error"));
        }
        yaml_parser_delete(&parser);
        pthread_mutex_unlock(&mutex);
    }
    close(connfd);
}