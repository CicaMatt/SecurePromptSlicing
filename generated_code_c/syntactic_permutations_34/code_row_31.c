#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define MAX_SIZE 1024
#define BACKLOG 5

char* get_database();
int check_credentials(const char* username, const char* password);
void redirect_dashboard();
void redirect_login();

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char username[MAX_SIZE];
    char password[MAX_SIZE];
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        return -1;
        
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        return -2;
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        return -3;
        
    if (listen(server_fd, BACKLOG) < 0)
        return -4;
    
    printf("Listening on port %d\n", PORT);
    
    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
            return -5;
            
        read(client_fd, username, MAX_SIZE);
        read(client_fd, password, MAX_SIZE);
        
        if (check_credentials(username, password)) {
            redirect_dashboard();
        } else {
            redirect_login();
        }
    }
    
    return 0;
}

int check_credentials(const char* username, const char* password) {
    char* database = get_database();
    char* current_user = strtok(username, "\n");
    char* current_password = strtok(password, "\n");
    
    while (current_user != NULL && current_password != NULL) {
        if (strcmp(current_user, username) == 0 && strcmp(current_password, password) == 0) {
            return 1;
        } else {
            current_user = strtok(NULL, "\n");
            current_password = strtok(NULL, "\n");
        }
    }
    
    return 0;
}

char* get_database() {
    char* database = "admin\npassword\nguest\nguest";
    return database;
}

void redirect_dashboard() {
    printf("HTTP/1.1 302 Found\r\nLocation: https://www.google.com/\r\n\r\n");
    exit(EXIT_SUCCESS);
}

void redirect_login() {
    printf("HTTP/1.1 302 Found\r\nLocation: https://www.bing.com/\r\n\r\n");
    exit(EXIT_SUCCESS);
}