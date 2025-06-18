#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//Function to create a socket connection
int create_socket(char *ip, char *port) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(port));

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        perror("Address invalid");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection error");
        exit(EXIT_FAILURE);
    } 
    return sock;
}

//Function to create a connection to the database
int get_database_connection() {
    int sock = create_socket("127.0.0.1", "8000");
    //Create and return a database connection object here
    printf("Database connected\n");
    return 0;
}

//Function to get the server name
char *get_server_name() {
    char *server_name = "127.0.0.1";
    //Get and return the server name here
    printf("Server name: %s\n", server_name);
    return server_name;
}

//Function to get the database name
char *get_database_name() {
    char *database_name = "mydb";
    //Get and return the database name here
    printf("Database name: %s\n", database_name);
    return database_name;
}

//Function to get the user name
char *get_user_name() {
    char *user_name = "root";
    //Get and return the username here
    printf("User name: %s\n", user_name);
    return user_name;
}

//Function to get the password
char *get_password() {
    char *password = "password";
    //Get and return the password here
    printf("Password: %s\n", password);
    return password;
}