// C code implementation of the idea

// include required headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
// define the size of our buffer, which is just the maximum packet size we expect to receive
#define BUFLEN 1024
 
// define a function that will get called each time there's an incoming connection
void accept_connection(int fd);
 
// define a function that will handle the HTTP request and send a response back
void respond_to_request(int client_socket);
 
// define a function that will check if the url is valid or not
bool redirect_invalid_url(const char *url);
 
// main function
int main() {
    // create an IPv4 socket, tell the OS we want to use TCP over IP, and automatically bind this socket to any available port
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    // define the address of the server
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8000);  // listen on port 8000
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
 
    // bind the socket to the defined address and port
    bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address));
 
    // listen on the server socket
    listen(server_fd, 10);
 
    // set up a loop that will run indefinitely to accept incoming connections and handle each one
    while (1) {
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
 
        int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_len);
        printf("Client connection received from %s:%d\n", inet_ntop(AF_INET, &client_address.sin_addr, client_address.sin_port));
 
        // call the function that will handle this connection
        accept_connection(client_fd);
    }
}
 
// function to handle each incoming connection
void accept_connection(int fd) {
    char buffer[BUFLEN];
    memset(&buffer, '\0', BUFLEN);
 
    // read the first line of the request from the client
    recv(fd, &buffer, BUFLEN, 0);
 
    // check if the HTTP method is GET
    char *method = strtok(buffer, " \t\r\n");
    if (strcasecmp(method, "GET") != 0) {
        send_error_response(fd, "405 Method Not Allowed", "Method not allowed");
        return;
    }
 
    // get the URL from the request line
    char *url = strtok(NULL, " \t");
 
    // check if the url is valid or not and send the response accordingly
    bool redirect = redirect_invalid_url(url);
    if (!redirect) {
        respond_to_request(fd);
    } else {
        send_error_response(fd, "403 Forbidden", "Invalid URL");
    }
}
 
// function to check the validity of the url
bool redirect_invalid_url(const char *url) {
    if (strncmp(url, "http://www.example.com", strlen("http://www.example.com")) == 0) {
        return false;
    }
    return true;
}
 
// function to send the response back to the client
void respond_to_request(int fd) {
    char buffer[BUFLEN];
    memset(&buffer, '\0', BUFLEN);
 
    // read the first line of the request from the client
    recv(fd, &buffer, BUFLEN, 0);
 
    // check if the HTTP method is GET
    char *method = strtok(buffer, " \t\r\n");
    if (strcasecmp(method, "GET") != 0) {
        send_error_response(fd, "405 Method Not Allowed", "Method not allowed");
        return;
    }
 
    // get the URL from the request line
    char *url = strtok(NULL, " \t");
 
    // create a curl handle
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
 
    if (curl) {
        // set the url option using the URL from the request line
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_perform(curl);
    }
 
    send(fd, "HTTP/1.1 302 Found\r\n", 21, 0);
    send(fd, "Location: http://www.example.com\r\n", 34, 0);
    send(fd, "\r\n", 2, 0);
 
    close(fd);
}