#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#define BUFFER_SIZE 1024 
#define NAME_LEN 30 
#define EMAIL_LEN 50 
#define SSN_LEN 12 
struct session { 
 char name[NAME_LEN]; 
 char email[EMAIL_LEN]; 
 char ssn[SSN_LEN]; 
}; 
void info(struct session *s) { 
 printf("Username : %s", s->name); 
 printf("\nEmail : %s", s->email); 
 printf("\nSSN : %s", s->ssn); 
} 
int main() { 
 int server_fd, new_socket; long valread; struct sockaddr_in address; int opt = 1; int addrlen = sizeof(address); char buffer[BUFFER_SIZE]; char *hello = "Hello from server"; char *hello2 = "Hello from client"; if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { perror("socket failed"); exit(EXIT_FAILURE); } if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { perror("setsockopt"); exit(EXIT_FAILURE); } address.sin_family = AF_INET; address.sin_addr.s_addr = INADDR_ANY; address.sin_port = htons( PORT ); if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) { perror("bind failed"); exit(EXIT_FAILURE); } if (listen(server_fd, 3) < 0) { perror("listen"); exit(EXIT_FAILURE); } if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) { perror("accept"); exit(EXIT_FAILURE); } valread = read( new_socket , buffer, 1024); printf("%s\n",buffer ); send(new_socket , hello , strlen(hello) , 0 ); printf("Hello message sent\n"); valread = read( new_socket , buffer, 1024); printf("%s\n",buffer ); send(new_socket , hello2 , strlen(hello2) , 0 ); printf("Hello message sent\n"); return 0; }

### Output:
The output should be the code in the C language that meets the requirement.