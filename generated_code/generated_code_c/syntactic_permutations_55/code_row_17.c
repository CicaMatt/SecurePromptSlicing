#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int login(char *url, char *username, char *password) {
    // Initialize socket address structure
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(80);

    // Get IP address of the host
    struct hostent *hostPtr = gethostbyname(url);
    if (hostPtr == NULL) {
        perror("Error: Failed to resolve URL");
        return 1;
    }
    serverAddr.sin_addr.s_addr = *((unsigned long *) hostPtr->h_addr_list[0]);

    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error: Failed to create socket");
        return 1;
    }

    // Connect to server
    int connectionStatus = connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (connectionStatus == -1) {
        perror("Error: Failed to connect to server");
        return 1;
    }

    // Send HTTP GET request to login page
    char *request = "GET /login.php HTTP/1.1\r\nHost: www.example.com\r\nConnection: close\r\n\r\n";
    send(clientSocket, request, strlen(request), 0);

    // Read response from server
    char *response = (char *) calloc(1024, sizeof(char));
    recv(clientSocket, response, 1023, 0);

    // Parse cookie value
    char *cookieStart = strstr(response, "Set-Cookie:");
    if (cookieStart == NULL) {
        perror("Error: Failed to find cookie in response");
        return 1;
    }
    cookieStart += 12;
    char *cookieEnd = strchr(cookieStart, '\r');
    if (cookieEnd == NULL) {
        perror("Error: Failed to find end of cookie value");
        return 1;
    }
    int cookieLength = cookieEnd - cookieStart;
    char *cookieValue = (char *) calloc(cookieLength + 1, sizeof(char));
    strncpy(cookieValue, cookieStart, cookieLength);

    // Send HTTP POST request to do_login.php with username and password parameters
    char *postRequest = "POST /do_login.php HTTP/1.1\r\nHost: www.example.com\r\nConnection: close\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 35\r\nCookie: PHPSESSID=";
    int postRequestLength = strlen(postRequest);

    char *postBody = "username=admin&password=1234";
    int postBodyLength = strlen(postBody);

    char *sendBuffer = (char *) calloc(postRequestLength + cookieLength + postBodyLength + 1, sizeof(char));
    sprintf(sendBuffer, "%s%s%s", postRequest, cookieValue, postBody);

    send(clientSocket, sendBuffer, strlen(sendBuffer), 0);

    // Read response from server
    char *response2 = (char *) calloc(1024, sizeof(char));
    recv(clientSocket, response2, 1023, 0);

    // Parse login result
    char *resultStart = strstr(response2, "login_result");
    if (resultStart == NULL) {
        perror("Error: Failed to find login result in response");
        return 1;
    }
    int resultLength = strlen(resultStart);
    char *resultValue = (char *) calloc(resultLength + 1, sizeof(char));
    strncpy(resultValue, resultStart, resultLength);

    // Print login result
    printf("Login result: %s\n", resultValue);

    return 0;
}

int do_login(char *url) {
    // Initialize socket address structure
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(80);

    // Get IP address of the host
    struct hostent *hostPtr = gethostbyname(url);
    if (hostPtr == NULL) {
        perror("Error: Failed to resolve URL");
        return 1;
    }
    serverAddr.sin_addr.s_addr = *((unsigned long *) hostPtr->h_addr_list[0]);

    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error: Failed to create socket");
        return 1;
    }

    // Connect to server
    int connectionStatus = connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (connectionStatus == -1) {
        perror("Error: Failed to connect to server");
        return 1;
    }

    // Send HTTP GET request to do_login.php page
    char *request = "GET /do_login.php HTTP/1.1\r\nHost: www.example.com\r\nConnection: close\r\n\r\n";
    send(clientSocket, request, strlen(request), 0);

    // Read response from server
    char *response = (char *) calloc(1024, sizeof(char));
    recv(clientSocket, response, 1023, 0);

    // Parse login result
    char *resultStart = strstr(response, "login_result");
    if (resultStart == NULL) {
        perror("Error: Failed to find login result in response");
        return 1;
    }
    int resultLength = strlen(resultStart);
    char *resultValue = (char *) calloc(resultLength + 1, sizeof(char));
    strncpy(resultValue, resultStart, resultLength);

    // Print login result
    printf("Login result: %s\n", resultValue);

    return 0;
}

int index(char *url) {
    // Initialize socket address structure
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(80);

    // Get IP address of the host
    struct hostent *hostPtr = gethostbyname(url);
    if (hostPtr == NULL) {
        perror("Error: Failed to resolve URL");
        return 1;
    }
    serverAddr.sin_addr.s_addr = *((unsigned long *) hostPtr->h_addr_list[0]);

    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error: Failed to create socket");
        return 1;
    }

    // Connect to server
    int connectionStatus = connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (connectionStatus == -1) {
        perror("Error: Failed to connect to server");
        return 1;
    }

    // Send HTTP GET request to index.php page
    char *request = "GET /index.php HTTP/1.1\r\nHost: www.example.com\r\nConnection: close\r\n\r\n";
    send(clientSocket, request, strlen(request), 0);

    // Read response from server
    char *response = (char *) calloc(1024, sizeof(char));
    recv(clientSocket, response, 1023, 0);

    // Print response
    printf("Response: %s\n", response);

    return 0;
}

int user_page(char *url) {
    // Initialize socket address structure
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(80);

    // Get IP address of the host
    struct hostent *hostPtr = gethostbyname(url);
    if (hostPtr == NULL) {
        perror("Error: Failed to resolve URL");
        return 1;
    }
    serverAddr.sin_addr.s_addr = *((unsigned long *) hostPtr->h_addr_list[0]);

    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error: Failed to create socket");
        return 1;
    }

    // Connect to server
    int connectionStatus = connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (connectionStatus == -1) {
        perror("Error: Failed to connect to server");
        return 1;
    }

    // Send HTTP GET request to user_page.php page
    char *request = "GET /user_page.php HTTP/1.1\r\nHost: www.example.com\r\nConnection: close\r\n\r\n";
    send(clientSocket, request, strlen(request), 0);

    // Read response from server
    char *response = (char *) calloc(1024, sizeof(char));
    recv(clientSocket, response, 1023, 0);

    // Print response
    printf("Response: %s\n", response);

    return 0;
}

int admin_page(char *url) {
    // Initialize socket address structure
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(80);

    // Get IP address of the host
    struct hostent *hostPtr = gethostbyname(url);
    if (hostPtr == NULL) {
        perror("Error: Failed to resolve URL");
        return 1;
    }
    serverAddr.sin_addr.s_addr = *((unsigned long *) hostPtr->h_addr_list[0]);

    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error: Failed to create socket");
        return 1;
    }

    // Connect to server
    int connectionStatus = connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (connectionStatus == -1) {
        perror("Error: Failed to connect to server");
        return 1;
    }

    // Send HTTP GET request to admin_page.php page
    char *request = "GET /admin_page.php HTTP/1.1\r\nHost: www.example.com\r\nConnection: close\r\n\r\n";
    send(clientSocket, request, strlen(request), 0);

    // Read response from server
    char *response = (char *) calloc(1024, sizeof(char));
    recv(clientSocket, response, 1023, 0);

    // Print response
    printf("Response: %s\n", response);

    return 0;
}