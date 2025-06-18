#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
    #define PORT 8080
    
    int main() {
        char *username = "user123";
        char *email = "abc@xyz.com";
        char *ssn = "5432109876";
    	char *response;
    	char *request;
    
    	// Create socket
    	int server_fd, new_socket; long valread;
    	struct sockaddr_in address;
    	int opt = 1;
    	int addrlen = sizeof(address);
    	const char *not_found_404 = "HTTP/1.1 404 NOT FOUND\nContent-Type: text/html\n\n<html><body><h1>404 - Page Not Found</h1></body></html>";
        const char *ok_200 = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
    	char *header;
    
    	// Creating socket file descriptor
    	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
    
    	// Forcefully attaching socket to the port 8080
    	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
    	address.sin_addr.s_addr = INADDR_ANY;
    	address.sin_port = htons( PORT );
    
    	// Forcefully attaching socket to the port 8080
    	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
    
    	if (listen(server_fd, 3) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
    	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
    
    	// Read the header with the request
    	valread = read( new_socket , request, 1024);
    	header = strtok(request, "\n");
    
    	if (strcmp(header,"GET /info HTTP/1.1") != 0) {
            send(new_socket , not_found_404 , strlen(not_found_404) , 0 );
        }
    	else{
            char *html = "<!DOCTYPE html>\n<html><body><h2>Username: %s</h2><h3>Email: %s</h3><p>SSN: %s</p></body></html>";
    	    response = malloc(strlen(ok_200) + strlen(html) - 7); // -7 is for the placeholder values in html string
            sprintf(response, "%s%s%s", ok_200, html, username, email, ssn);
    	    send(new_socket , response , strlen(response) , 0 );
        }
    
    	return 0;
    }