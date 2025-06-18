/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Defines */
#define PORT 80
#define MAX_BUF_SIZE 1024
#define USERNAME "myusername"
#define PASSWORD "mypassword"
#define REDIRECT_URL "http://www.google.com/"

/* Functions */
void processRequest(int socket);
void readRequest(int socket, char * requestBuf, int bufSize);
void sendResponse(int socket, const char * responseData);

/* Main function */
int main() {
   int listenSocket = -1;
   struct sockaddr_in serverAddr, clientAddr;
   socklen_t addrLen = sizeof(clientAddr);
   int clientSocket = -1;

   /* Create a socket */
   if ((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("socket() failed");
      return EXIT_FAILURE;
   }

   /* Configure server address to listen on all available interfaces */
   memset(&serverAddr, 0, sizeof(serverAddr));
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   serverAddr.sin_port = htons(PORT);

   /* Bind the socket to the address and port */
   if (bind(listenSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
      perror("bind() failed");
      return EXIT_FAILURE;
   }

   /* Listen on the socket */
   if (listen(listenSocket, 5) < 0) {
      perror("listen() failed");
      return EXIT_FAILURE;
   }

   printf("Listening for connections on port %d...\n", PORT);

   /* Run forever */
   while (1) {

      /* Accept client connection */
      if ((clientSocket = accept(listenSocket, (struct sockaddr *) &clientAddr, &addrLen)) < 0) {
         perror("accept() failed");
         return EXIT_FAILURE;
      }

      printf("Accepted connection from client: %s\n", inet_ntoa(clientAddr.sin_addr));

      /* Process client request */
      processRequest(clientSocket);

      /* Close the connected socket */
      close(clientSocket);
   }
}

/* Processes a single client request */
void processRequest(int clientSocket) {
   char * requestBuf = NULL;
   size_t bufSize = 0, dataLen = 0;
   char username[MAX_BUF_SIZE];
   char password[MAX_BUF_SIZE];
   int matchFound = 0;

   /* Allocate memory for the request buffer */
   if ((requestBuf = malloc(bufSize * sizeof(*requestBuf))) == NULL) {
      perror("malloc() failed");
      return EXIT_FAILURE;
   }

   /* Read data from client */
   readRequest(clientSocket, requestBuf, bufSize);

   /* Check if the username and password are correct */
   if (strncmp(username, USERNAME, strlen(USERNAME)) == 0 && strncmp(password, PASSWORD, strlen(PASSWORD)) == 0) {
      matchFound = 1;
   }

   /* Send response to client */
   if (matchFound) {
      sendResponse(clientSocket, REDIRECT_URL);
   } else {
      sendResponse(clientSocket, "Incorrect username or password");
   }
}

/* Reads data from the specified socket into the request buffer */
void readRequest(int clientSocket, char * requestBuf, int bufSize) {
   ssize_t numRead = 0;
   size_t totalRead = 0;

   while ((numRead = recv(clientSocket, (requestBuf + totalRead), (bufSize - totalRead), 0)) > 0) {
      totalRead += numRead;
   }
}

/* Sends the specified response data to the client */
void sendResponse(int clientSocket, const char * responseData) {
   size_t responseLen = strlen(responseData);
   ssize_t numSent = 0;
   size_t totalSent = 0;

   while ((numSent = send(clientSocket, (responseData + totalSent), (responseLen - totalSent), 0)) > 0) {
      totalSent += numSent;
   }
}