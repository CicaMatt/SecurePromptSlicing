#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include "picohttpparser.h"
#include "qs_parse.h"

/*
  gcc -o server server.c picohttpparser.c qs_parse.c -lssl -lcrypto -lpthread -lm
*/

// Global variables
int listenfd;
void error(char *msg) { perror(msg); exit(0); }

static const char *REQUEST_METHOD[9] = {"GET", "HEAD", "POST", "PUT", "DELETE", "CONNECT", "OPTIONS", "TRACE", "PATCH"};

void handler(int sig) {
    // handle signals
    printf("signal handled: %d\n", sig);
}

// Define an http header struct
struct HttpHeader {
  char *name;
  char *value;
};

// A linked list for storing http headers
typedef struct llnode {
  void *data;
  struct llnode *next;
} llnode;

// Define a request struct
struct HttpRequest {
  int method;
  char* target;
  char* version;
  struct llnode* headers;
};

/*
 * Function to parse the raw http request and extract method, target, and version
 */
struct HttpRequest* parse_request(char* req) {
    struct phr_header headers[100];
    size_t buflen = 0, prevbuflen = 0;
    size_t msglen = 0;
    char *method, *path=NULL, *version;
    int i, minor_version;
    struct HttpRequest* request = NULL;

    // Parse the raw http request
    req = parse_http_request(req, &method, &path, &version, headers, 100, &buflen);
    if (req == NULL) {
      printf("Failed to parse HTTP request\n");
      return NULL;
    }

    // Print the parsed request
    printf("\n\nHTTP Request: \n");
    for(i = 0; i < buflen && req[i] != '\0'; i++) {
        printf("%c", isprint(req[i]) ? req[i] : '.');
    }
    //printf("HTTP Request: %s\n", req);
    printf("\n");

    request = malloc(sizeof(struct HttpRequest));
    if (request == NULL) {
      printf("Failed to allocate memory for http request struct\n");
      return NULL;
    }

    // Save the method, target, and version in the request struct
    request->method = 0;
    for(i = 0; i < sizeof(REQUEST_METHOD)/sizeof(char *); i++) {
        if (strcmp(method, REQUEST_METHOD[i]) == 0) {
            request->method = i+1; // method is an index to the REQUEST_METHOD enum
            break;
        }
    }

    request->target = path;
    request->version = version;

    printf("Method: %s\n", method);
    printf("Target: %s\n", path);
    printf("Version: %s\n", version);

    // Parse the http headers
    for (i=0; i<buflen; i++) {
        if (headers[i].name) {
            char *header_name = headers[i].name;
            char *header_value = headers[i].value;

            printf("Header name: %s, Header value: %s\n", header_name, header_value);
        }
    }

    return request;
}

/*
 * Function to create a linked list of http headers
 */
llnode* create_header(char* name, char* value) {
  llnode* node = (llnode*)malloc(sizeof(llnode));
  if (node == NULL) {
    printf("Failed to allocate memory for http header\n");
    return NULL;
  }

  struct HttpHeader *header = (struct HttpHeader *) malloc(sizeof(struct HttpHeader));
  if (header == NULL) {
      free(node);
      printf("Failed to allocate memory for http header\n");
      return NULL;
  }

  // Save the name and value in the header struct
  header->name = name;
  header->value = value;

  node->data = header;
  node->next = NULL;

  return node;
}

/*
 * Function to add a header to the linked list of http headers
 */
void add_header(llnode* head, char* name, char* value) {
    llnode* current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = create_header(name, value);
}

/*
 * Function to print the linked list of http headers
 */
void print_headers(llnode* head) {
  if (head == NULL) {
      printf("Header list is empty\n");
      return;
  }

  llnode* current = head->next;
  while (current != NULL) {
    struct HttpHeader *header = current->data;
    printf("Name: %s, Value: %s\n", header->name, header->value);
    current = current->next;
  }
}

/*
 * Function to generate the http response
 */
void* generate_response(struct HttpRequest* request) {
    char* status_code = "200 OK";
    char* content_type = "text/html";
    char* body = "<html><body>User Info</body></html>";
    char* response = NULL;

    // Generate the http response
    response = calloc(1, 4096);
    if (response == NULL) {
      printf("Failed to allocate memory for HTTP response\n");
      return NULL;
    }

    sprintf(response, "HTTP/1.1 %s\r\nContent-Type: %s; charset=utf-8\r\nContent-Length: %ld\r\n\r\n%s", status_code, content_type, strlen(body), body);

    printf("\nHTTP Response:\n%s\n", response);

    return response;
}

/*
 * Function to handle the http request and generate the response
 */
void* handler_request(char* req) {
  struct HttpRequest* request = NULL;
  void* resp = NULL;

  // Parse the raw http request
  printf("\nParsing HTTP Request...\n");
  request = parse_request(req);
  if (request == NULL) {
    printf("Failed to parse HTTP request\n");
    return NULL;
  }

  // Check for null pointers in the request struct
  if (request->method == 0 || request->target == NULL || request->version == NULL) {
      free(request);
      printf("Invalid HTTP Request\n");
      return NULL;
  }

  // Generate the http response
  printf("\nGenerating HTTP Response...\n");
  resp = generate_response(request);

  if (request != NULL) {
    free(request->target);
    free(request->version);
    request->target = NULL;
    request->version = NULL;
    free(request);
  }

  return resp;
}

/*
 * Function to handle the client connection
 */
void handle_connection(int connfd) {
  char buf[4096];
  void* response = NULL;

  // Read data from socket
  printf("Reading data from socket...\n");
  int n = read(connfd, buf, 4096);
  if (n < 0) error("ERROR reading from socket");
  else if (n == 0) {
    // Close connection if there is no more data to be sent or received
    printf("\nNo more data\n");
    close(connfd);
    return;
  }

  buf[n] = '\0';
  printf("Received: %s\n", buf);

  // Handle the http request and generate response
  response = handler_request(buf);
  if (response == NULL) {
      close(connfd);
      return;
  }

  // Send the http response back to client
  printf("Sending response...\n");
  n = write(connfd, response, strlen(response));
  if (n < 0) error("ERROR writing to socket");

  free(response);
  return;
}

/*
 * Function to handle the server connections
 */
void start_server() {
    int connfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    signal(SIGPIPE, handler); // Handle broken pipe signal

    while (1) {
        // Accept connection from client
        connfd = accept(listenfd, (struct sockaddr*) &cli_addr, &clilen);
        if (connfd < 0) error("ERROR on accept");

        handle_connection(connfd);
    }
}

/*
 * Function to start the server
 */
void init_server() {
    int portno = 8080;
    struct sockaddr_in serv_addr;
    signal(SIGPIPE, handler); // Handle broken pipe signal

    // Create a socket point
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // Bind socket to the address and port
    if (bind(listenfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      error("ERROR on binding");
    }

    printf("\nListening on port %d...\n", portno);

    // Listen for incoming connections
    listen(listenfd, 5);
}

/*
 * Main function
 */
int main() {
    init_server();
    start_server();

    return 0;
}