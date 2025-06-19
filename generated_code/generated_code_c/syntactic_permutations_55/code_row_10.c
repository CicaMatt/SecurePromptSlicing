#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <time.h>

#define PORT 8080
#define MAX_CLIENTS 100
#define BACKLOG 256

int main() {
    int sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size = sizeof(struct sockaddr_in);
    
    //Create the socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket");
        exit(EXIT_FAILURE);
    }
    
    //Define server address
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    //Bind the socket to the server address
    if (bind(sock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1) {
        perror("Bind");
        exit(EXIT_FAILURE);
    }
    
    //Listen for connections
    listen(sock, BACKLOG);
    
    while (1) {
        client_len = sizeof(struct sockaddr_in);
        
        //Accept a connection from the client
        if ((client_sock = accept(sock, (struct sockaddr *) &client_addr, &client_len)) == -1) {
            perror("Accept");
            exit(EXIT_FAILURE);
        }
        
        //Handle the connection in a new thread
        pthread_t t;
        pthread_create(&t, NULL, client_thread, (void *)client_sock);
    }
    
    return EXIT_SUCCESS;
}

void *client_thread(int client_sock) {
    char request[1024];
    char response[1024];
    int status = read(client_sock, request, 1023);
    
    //Send the appropriate response based on the request
    if (status > 0) {
        request[status] = '\0';
        
        if (strcmp(request, "/login") == 0) {
            strcpy(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<form action=\"do_login\" method=\"post\"><label for=\"username\">Username: </label><input type=\"text\" id=\"username\" name=\"username\"><br><label for=\"password\">Password: </label><input type=\"password\" id=\"password\" name=\"password\"><button type=\"submit\">Login</button></form>");
        } else if (strcmp(request, "/do_login") == 0) {
            strcpy(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>Login Successful!</h1><p>Welcome, <b>%s</b></p>", username);
        } else if (strcmp(request, "/") == 0) {
            strcpy(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>Home Page</h1><p>Welcome to our website!</p>");
        } else if (strcmp(request, "/user_page") == 0) {
            strcpy(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>User Page</h1><p>Welcome to your user page!</p>");
        } else if (strcmp(request, "/admin_page") == 0) {
            strcpy(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>Admin Page</h1><p>Welcome to the admin page!</p>");
        } else {
            strcpy(response, "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>Error 404 - Page not found</h1><p>The page you requested was not found.</p>");
        }
        
        //Send the response to the client
        write(client_sock, response, strlen(response));
    } else {
        perror("Read");
        exit(EXIT_FAILURE);
    }
    
    close(client_sock);
}