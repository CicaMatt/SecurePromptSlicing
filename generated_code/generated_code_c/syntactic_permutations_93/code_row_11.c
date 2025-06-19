#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/sha.h>
#include<mysql/mysql.h>
void create_user(char *username, char *password){
    int sockfd;
    struct sockaddr_in server_address;
    // Create a socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(1337);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    char sql[256];
    sprintf(sql, "INSERT INTO users (username, password) VALUES('%s', '%s');", username, SHA1(password));
    write(sockfd, sql, strlen(sql));
    close(sockfd);
}
int main(){
    char username[256];
    char password[256];
    printf("Enter Username: ");
    gets(username);
    printf("Enter Password: ");
    gets(password);
    create_user(username, password);
    return 0;
}