#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define BUFFER_SIZE 4096

void handleClient(int clientSocket, const char *uploadDir) {
    char buffer[BUFFER_SIZE];
    int bytesRead;
    FILE *file;

    // Read the HTTP request from the client
    bzero(buffer, BUFFER_SIZE);
    if ((bytesRead = read(clientSocket, buffer, BUFFER_SIZE - 1)) < 0) {
        perror("Error reading from socket");
        close(clientSocket);
        return;
    }

    printf("Received HTTP Request:\n%s\n", buffer);

    // Extract filename from the request (simple parsing for demonstration)
    char *filename = strstr(buffer, "filename=\"") + strlen("filename=\"");
    if (!filename) {
        perror("Filename not found in request");
        close(clientSocket);
        return;
    }
    char *end = strchr(filename, '\"');
    if (!end) {
        perror("Invalid filename format");
        close(clientSocket);
        return;
    }
    size_t len = end - filename;
    char *fileToSave = malloc(len + 1);
    strncpy(fileToSave, filename, len);
    fileToSave[len] = '\0';

    // Create full path for the uploaded file
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s", uploadDir, fileToSave);

    // Open the file to save the data
    if ((file = fopen(filePath, "wb")) == NULL) {
        perror("Failed to open file");
        close(clientSocket);
        free(fileToSave);
        return;
    }

    // Read and write the content of the request (PDF data)
    bzero(buffer, BUFFER_SIZE);
    while ((bytesRead = read(clientSocket, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, sizeof(char), bytesRead, file);
    }
    
    fclose(file);

    char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile uploaded successfully.\n";
    write(clientSocket, response, strlen(response));

    printf("File '%s' has been uploaded to %s\n", fileToSave, uploadDir);
    
    free(fileToSave);
    close(clientSocket);
}

void startServer(int port, const char *uploadDir) {
    int serverFd, clientSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    // Prepare the sockaddr_in structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Bind
    if (bind(serverFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(serverFd);
        exit(EXIT_FAILURE);
    }

    // Listen
    listen(serverFd, 3);

    printf("Server started on port %d\n", port);

    while (1) {
        clientSocket = accept(serverFd, NULL, NULL);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }
        
#ifdef _WIN32
        HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)handleClient, (LPVOID)(size_t)clientSocket, 0, NULL);
#else
        pid_t pid = fork();
        if (pid == 0) {
            close(serverFd);
            handleClient(clientSocket, uploadDir);
            exit(0);
        }
#endif
    }

#ifdef _WIN32
    CloseHandle(thread);
#endif

    close(serverFd);
}

int main(int argc, char *argv[]) {
    int port = 8080;
    const char *uploadDir = "uploads";

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return EXIT_FAILURE;
    }
#endif

    // Ensure uploads directory exists
    mkdir(uploadDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    startServer(port, uploadDir);

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}