#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>
#include<pthread.h>
#include<ctype.h>

#define PORT 5000
#define BUFFERSIZE 2048

char* root = NULL;
char* index_html = NULL;
char* login_html = NULL;
char* secret_html = NULL;

void initServer(){
    int sockfd, newsockfd, clilen;
    struct sockaddr_in server_address, client_address;
    pthread_t thread_id;

    /* Create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    listen(sockfd,5);

    clilen = sizeof(client_address);

    while (1){
        newsockfd = accept(sockfd,(struct sockaddr *) &client_address, &clilen);

        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }

        pthread_create(&thread_id, NULL, serveClient, (void*)&newsockfd);
    }
}

char* get_page(int sockfd){
    char buffer[BUFFERSIZE];
    bzero(buffer, BUFFERSIZE);
    int n = recv(sockfd, buffer, BUFFERSIZE-1, 0);

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    char* pch = strtok(buffer," ");

    while (pch != NULL){
        if (strcmp(pch, "GET") == 0){
            pch = strtok(NULL, " /");
            break;
        }
        pch = strtok(NULL, "/");
    }

    return pch;
}

void* serveClient(void* arg) {
    int sockfd = *((int*)arg);
    char buffer[BUFFERSIZE];
    bzero(buffer, BUFFERSIZE);

    char* page = get_page(sockfd);

    if (strcmp(page, "favicon.ico") == 0){
        send(sockfd, "HTTP/1.0 404 NOT FOUND\r\n", 23, 0);
        return;
    } else if (strcmp(page, "login") == 0) {
        send(sockfd, login_html, strlen(login_html), 0);
    } else if (strcmp(page, "index.html") == 0) {
        send(sockfd, index_html, strlen(index_html), 0);
    } else if (strcmp(page, "secret.html") == 0){
        char* session = get_session(sockfd);
        if(strcmp(session, "admin:12345") == 0) {
            send(sockfd, secret_html, strlen(secret_html), 0);
        } else {
            send(sockfd, "HTTP/1.0 401 Unauthorized\r\n", 27, 0);
        }
    }
    close(sockfd);
}

char* get_session(int sockfd){
    char buffer[BUFFERSIZE];
    bzero(buffer, BUFFERSIZE);
    int n = recv(sockfd, buffer, BUFFERSIZE-1, 0);

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    char* pch = strtok(buffer,"Cookie: ");
    while (pch != NULL){
        if (strcmp(pch, "session") == 0){
            break;
        }
        pch = strtok(NULL, ";");
    }

    return pch;
}

void set_session(int sockfd, char* session){
    char buffer[BUFFERSIZE];
    bzero(buffer, BUFFERSIZE);

    sprintf(buffer,"HTTP/1.0 302 FOUND\r\nLocation: /secret.html\r\nSet-Cookie: %s\r\n\r\n", session);

    send(sockfd, buffer, strlen(buffer), 0);
}

void do_login(int sockfd){
    char buffer[BUFFERSIZE];
    bzero(buffer, BUFFERSIZE);
    int n = recv(sockfd, buffer, BUFFERSIZE-1, 0);

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    char* pch = strtok(buffer,"&=");
    int i = 0;

    while (pch != NULL){
        if(i == 2) {
            break;
        }
        if (strcmp(pch, "username") == 0) {
            pch = strtok(NULL,"&=");
            i++;
        } else if (strcmp(pch, "password") == 0){
            pch = strtok(NULL, "&=");
            i++;
        }
    }

    if (strcmp(pch, "admin:12345") == 0) {
        set_session(sockfd, pch);
    } else {
        send(sockfd, "HTTP/1.0 401 Unauthorized\r\n", 27, 0);
    }
}

int main(){
    root = (char*)malloc(BUFFERSIZE*sizeof(char));
    index_html = (char*)malloc(BUFFERSIZE*sizeof(char));
    login_html = (char*)malloc(BUFFERSIZE*sizeof(char));
    secret_html = (char*)malloc(BUFFERSIZE*sizeof(char));

    strcpy(root, "./www");
    strcpy(index_html, "<a href='/login'>Login</a>");
    strcpy(login_html, "<form method='POST' action='/do_login'><input type='text' name='username' /><input type='password' name='password' /><input type='submit' value='Submit' /></form>");
    strcpy(secret_html, "<p>Secret settings</p>");

    initServer();

    return 0;
}