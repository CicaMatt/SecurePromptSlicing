#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>
#include <pthread.h>
#define MAX_REQUEST_LEN 4096
#define MAX_HEADERS 16
#define BUFFER_SIZE 8192
struct Request {
    char *method, *path, *version;
    int numHeaders;
    struct Header {
        char *name, *value;
    } headers[MAX_HEADERS];
};
typedef struct {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    size_t offset;
} ClientStream;
struct Response {
    int statusCode;
    char *statusMessage;
    int numHeaders;
    struct Header {
        char *name, *value;
    } headers[MAX_HEADERS];
    const char *body;
};
typedef enum { FALSE, TRUE } bool;
static void printError(const char *format, ...);
static void printRequest(struct Request *request);
static void printResponse(struct Response *response);
static char *readLine(char *buffer, size_t n, FILE *fp);
static int parseRequest(char *buffer, struct Request *request);
static void processRequest(int clientSocket, ClientStream stream);
static struct Response makeErrorResponse(int statusCode, const char *statusMessage);
static struct Response makeSuccessResponse(const char *body);
static bool isAlpha(char c);
static bool isDigit(char c);
static bool isSpace(char c);
static void printHelp();
void printUsage();
int main(int argc, char *argv[]) {
    int serverSocket;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (argc != 2) {
        printUsage();
        return 1;
    }
    int status = getaddrinfo(NULL, argv[1], &hints, &result);
    if (status != 0) {
        printError("getaddrinfo error: %s\n", gai_strerror(status));
        return 2;
    }
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        serverSocket = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (serverSocket == -1) {
            continue;
        }
        if (bind(serverSocket, rp->ai_addr, rp->ai_addrlen) != -1) {
            break;
        }
    }
    if (rp == NULL) {
        printError("Could not bind\n");
        return 3;
    }
    freeaddrinfo(result);
    int enable = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        printError("Could not set socket option\n");
        return 4;
    }
    if (listen(serverSocket, SOMAXCONN) != -1) {
        char server[INET6_ADDRSTRLEN];
        int clientSocket = accept(serverSocket, NULL, NULL);
        close(serverSocket);
        socklen_t addrlen = sizeof(struct sockaddr_storage);
        getpeername(clientSocket, (struct sockaddr *)server, &addrlen);
        printf("Connection from %s\n", server);
        ClientStream stream;
        stream.fp = fdopen(clientSocket, "r");
        if (!stream.fp) {
            printError("Could not open socket for reading\n");
            return 5;
        }
        processRequest(clientSocket, stream);
        fclose(stream.fp);
    } else {
        printError("Could not listen on socket\n");
        return 6;
    }
    return 0;
}
static void printUsage() {
    printf("Usage: %s <port>\n", "web-server");
}
void printHelp() {
    printf("\nUsage:\n");
    printf("%s <port>\n\n", "web-server");
    printf("Options:\n");
    printf("  -h, --help                 Show this help message and exit.\n");
    printf("  -v, --version              Print version information and quit.\n\n");
}
static void printError(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}
static void processRequest(int clientSocket, ClientStream stream) {
    char buffer[MAX_REQUEST_LEN];
    readLine(buffer, MAX_REQUEST_LEN, stream.fp);
    struct Request request;
    if (parseRequest(buffer, &request)) {
        printf("Invalid request\n");
        return;
    }
    printRequest(&request);
}
static void printRequest(struct Request *request) {
    printf("%s %s %s", request->method, request->path, request->version);
    for (int i = 0; i < request->numHeaders; i++) {
        struct Header header = request->headers[i];
        printf("\n%s: %s", header.name, header.value);
    }
    printf("\n\n");
}
static int parseRequest(char *buffer, struct Request *request) {
    char *line = strtok(buffer, "\r\n");
    if (line == NULL) return 1;
    char *next = strchr(line, ' ');
    if (next == NULL) return 2;
    request->method = line;
    size_t methodLen = next - line;
    line += methodLen + 1;
    request->path = line;
    next = strchr(line, ' ');
    if (next == NULL) return 3;
    size_t pathLen = next - line;
    request->version = next + 1;
    line += pathLen + 2;
    int numHeaders = 0;
    while (*line != '\n' && *line != '\r') {
        char *next = strchr(line, ':');
        if (next == NULL) return 4;
        struct Header header;
        header.name = line;
        size_t nameLen = next - line;
        line += nameLen + 1;
        while (*line == ' ') line++;
        header.value = line;
        request->headers[numHeaders++] = header;
        if (next == NULL) return 5;
    }
    request->numHeaders = numHeaders;
    return 0;
}
static void printResponse(struct Response *response) {
    printf("%s %d\n", response->statusCode, response->statusMessage);
    for (int i = 0; i < response->numHeaders; i++) {
        struct Header header = response->headers[i];
        printf("\n%s: %s", header.name, header.value);
    }
}
static char *readLine(char *buffer, size_t n, FILE *fp) {
    if (fgets(buffer, n - 1, fp)) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        return buffer;
    }
}
static bool isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}
static bool isSpace(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}