#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mysql/mysql.h>
#include <pthread.h>
 
#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "mailing_list"
#define PORT 3306
 
void unsubscribe(char *email);
void *handle_request(void *arg);
 
int main() {
    int socketfd, clientsock;
    socklen_t client_len;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    pthread_t tid;
 
    // Create the socket
    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    // Set up the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
 
    // Bind to the socket
    if (bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
 
    // Listen for connections
    if (listen(socketfd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
 
    while (1) {
        printf("Listening for connections...\n");
 
        // Accept an incoming connection
        client_len = sizeof(client_addr);
        if ((clientsock = accept(socketfd, (struct sockaddr *)&client_addr, &client_len)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
 
        // Create a thread to handle the connection
        if (pthread_create(&tid, NULL, handle_request, (void *)&clientsock) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
}
 
void *handle_request(void *arg) {
    int clientsock = *((int *)arg);
    char buffer[1024];
    char email[100];
 
    // Receive the email parameter from the GET request
    recv(clientsock, buffer, 1024, 0);
    sscanf(buffer, "%[^&]", email);
 
    // Check if the email is in the database
    MYSQL *conn;
    conn = mysql_init(NULL);
 
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, PORT, NULL, 0)) {
        printf("Connection failed\n");
    }
 
    char query[256];
    sprintf(query, "SELECT * FROM mailing_list WHERE email='%s'", email);
    mysql_query(conn, query);
 
    MYSQL_RES *result = mysql_store_result(conn);
 
    if (mysql_num_rows(result) == 1) {
        // The email is in the database, so unsubscribe the user
        sprintf(query, "DELETE FROM mailing_list WHERE email='%s'", email);
        mysql_query(conn, query);
 
        char message[256];
        sprintf(message, "You have been unsubscribed from our mailing list");
        send(clientsock, message, strlen(message), 0);
    } else {
        // The email is not in the database, so return an error message
        char message[256];
        sprintf(message, "You are already unsubscribed from our mailing list");
        send(clientsock, message, strlen(message), 0);
    }
 
    // Close the connection
    mysql_free_result(result);
    mysql_close(conn);
    close(clientsock);
}