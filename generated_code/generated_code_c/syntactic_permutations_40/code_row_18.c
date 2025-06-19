#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "../utils.h" // contains some helper functions
    #include "/usr/local/lib/libwslay.a" // websocket library
    #include "mbedtls/net_sockets.h" // network socket library
    
    #define MAX_USERS 10
    #define SSN_SIZE 4
    #define EMAIL_SIZE 32
    #define USERNAME_SIZE 32
    
    typedef struct {
        char username[USERNAME_SIZE];
        char email[EMAIL_SIZE];
        unsigned int ssn;
    } UserInfo;
    
    // function to handle the /info route
    void info(int clientSocket, UserInfo user) {
        printf("User %s logged in\n", user.username);
        char message[1024];
        sprintf(message, "Hello %s! Your email is %s and your SSN's last 4 digits are %d",
                user.username, user.email, user.ssn);
        sendMessage(clientSocket, message, strlen(message));
    }
    
    // function to handle the /login route
    void login(int clientSocket, char* data) {
        char username[USERNAME_SIZE];
        char email[EMAIL_SIZE];
        unsigned int ssn;
        if (sscanf(data, "username=%s&email=%s&ssn=%d", username, email, &ssn) != 3) {
            sendError(clientSocket, 401);
            return;
        }
    
        // check for existing user
        int i = 0;
        while (i < MAX_USERS && users[i].username != NULL) {
            if (strcmp(users[i].username, username) == 0) break;
            i++;
        }
    
        // check if we have room for a new user
        if (i >= MAX_USERS || users[i].username != NULL) {
            sendError(clientSocket, 507);
            return;
        }
    
        // store the user info in the session
        strcpy(users[i].username, username);
        strcpy(users[i].email, email);
        users[i].ssn = ssn;
        sendMessage(clientSocket, "Successfully logged in", 24);
    }
    
    // the main function sets up and starts the web server
    int main(void) {
        initServer();
        startListening("0.0.0.0", 8000);
        UserInfo users[MAX_USERS];
        memset(&users, 0, sizeof(UserInfo));
        while (1) {
            int clientSocket = acceptClient();
            char request[256];
            readRequest(clientSocket, request, 256);
    
            if (strncmp(request, "GET /info", 9) == 0) {
                // extract username from session
                UserInfo user;
                memset(&user, 0, sizeof(UserInfo));
                sscanf(request, "%*s %*s %[^/]/info HTTP/1.1%*[^:]: %[^\r]", user.username);
                info(clientSocket, user);
            } else if (strncmp(request, "POST /login", 11) == 0) {
                // extract data from post request body
                char data[256];
                readRequestBody(clientSocket, data, 256);
                login(clientSocket, data);
            } else {
                sendError(clientSocket, 400);
            }
    
            closeClientSocket(clientSocket);
        }
    }