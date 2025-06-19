#include <stdio.h>   /* C Standard Library for Input and Output */
#include <stdlib.h>  /* Standard C library includes stdio.h, stddef.h and stdarg.h */
#include <string.h>  /* String handling functions such as strcmp(), strcpy() and strcat() */
#include <stdbool.h> /* Boolean type support in C99 */
#include <unistd.h>  /* Provides the fork, exec, exit, getpid, read, write, and close system calls */
#include <sys/wait.h> /* Defines macros for the wait() function */
#include <sys/types.h> /* Needed for socket types */
#include <netinet/in.h> /* Internet domain sockets */ 
#include <signal.h>     /* Signal handling library */
#include <time.h>       /* Time related functions (e.g., time()) */
#include <syslog.h>     /* Functions to log messages to the system log */

/* Define max message size and socket domain type */
#define BUFSIZE 1024
#define DOMAIN AF_INET

/* Define message handling function prototype */
void handleMessage(int, int);

int main() {

    /* Declare variables */
    int serverSocket;   /* Socket descriptor for the server socket */
    int clientSocket;   /* Socket descriptor for the client socket */
    struct sockaddr_in serverAddr;  /* Server address information */
    struct sockaddr_in clientAddr;  /* Client address information */
    int addrLen = sizeof(struct sockaddr_in);  /* Length of address structures */
    char buffer[BUFSIZE];   /* I/O buffer */

    // Create the server socket (IPv4, stream-based, protocol likely set to TCP)
    if ((serverSocket = socket(DOMAIN, SOCK_STREAM, 0)) < 0){
        perror("Unable to create socket");
        exit(1);
    }
    
    // Configure server address structure contains (0.0.0.0 is the IP address and 5432 is the port)
    memset(&serverAddr, 0, sizeof(serverAddr));  /* Zero out structure */
    serverAddr.sin_family = DOMAIN;              /* IPv4 domain */
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any available address on the local machine */
    serverAddr.sin_port = htons(5432);           /* Server port */
    
    // Bind the socket to a specific network interface and port number using the address information in servaddr
    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        perror("Unable to bind");
        exit(1);
    }
    
    // Listen for incoming connections on the server socket
    if (listen(serverSocket, 5) < 0){
        perror("Listen error");
        exit(1);
    }

    while (1) {
        
        // Wait for a client to connect to the server using accept()
        if ((clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, (socklen_t*)&addrLen)) < 0){
            perror("Unable to connect");
            exit(1);
        }
        
        // Handle the message from the client
        handleMessage(clientSocket, serverSocket);
    }
    
}

/* Function for handling messages from clients */
void handleMessage(int clientSocket, int serverSocket) {

    // Receive a message from the client (recv())
    memset(&buffer, 0, BUFSIZE);
    recv(clientSocket, buffer, BUFSIZE, 0);
    
    // Extract the username and email address from the message received from the client.
    char *username = strtok(buffer,"&");
    char *email = strtok(NULL,"\n");

    // Get the last four digits of the social security number (the last 4 characters)
    char *ssNumber = strtok(NULL, "\0");
    
    if (username != NULL && email != NULL && ssNumber != NULL){
       
       // Send a response message to the client using send(). The first argument is the socket descriptor for the client. 
       //The second argument contains the message to be sent; it should include the username, email address and social security number. 
       char *message = malloc(BUFSIZE);
       memset(message, '\0', BUFSIZE);
       
       strcpy(message, "Welcome ");
       strcat(message, username);
       strcat(message, "\n");
       strcat(message, email);
       strcat(message, "\n");
       strcat(message, ssNumber);
       
       send(clientSocket, message, BUFSIZE, 0);
    } else {
        // Log the error
        syslog(LOG_INFO | LOG_USER, "Message format error\n");
        
        // Send an error message to the client using send(). 
        char *message = malloc(BUFSIZE);
        memset(message, '\0', BUFSIZE);
        strcpy(message, "Error: Message format incorrect\n");
        send(clientSocket, message, BUFSIZE, 0);
    }
    
    // Close the client socket using close()
    close(clientSocket);
}