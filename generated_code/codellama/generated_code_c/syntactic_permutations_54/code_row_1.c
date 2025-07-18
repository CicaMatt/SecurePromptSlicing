#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void login();
int do_login(char *username, char *password);
void admin_page();

int main(){
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd == -1){
        printf("Error creating a socket!\n");
        return -1;
    }

    struct sockaddr_in server_address;
    memset(&server_address, '\0', sizeof(struct sockaddr_in));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(80);
    inet_aton("127.0.0.1", &server_address.sin_addr);

    if(connect(client_fd, (struct sockaddr *)&server_address, sizeof(struct sockaddr)) == -1){
        printf("Error connecting to the server!\n");
        close(client_fd);
        return -2;
    }

    char request[BUFSIZ], response[BUFSIZ];

    // login form
    sprintf(request, "GET /login.html HTTP/1.0\r\n\r\n");
    if(write(client_fd, request, strlen(request)) == -1){
        printf("Error sending request to the server!\n");
        close(client_fd);
        return -3;
    }

    if(read(client_fd, response, BUFSIZ) == -1){
        printf("Error reading response from the server!\n");
        close(client_fd);
        return -4;
    }
    
    char username[BUFSIZ], password[BUFSIZ];
    int is_admin = 0;
    char *ptr = strstr(response, "<form");
    if(ptr != NULL){
        ptr += 5;
        while(*ptr != '\n'){
            username[*ptr] = *ptr++;
        }
        printf("Username: ");
        scanf("%s",username);
        
        printf("Password: ");
        scanf("%s",password);
    }
    
    is_admin = do_login(username, password);
    if(is_admin){
        admin_page();
    }else{
        return 0;
    }
}