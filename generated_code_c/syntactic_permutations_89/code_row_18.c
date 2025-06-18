#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>
#include<ctype.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "http_parsing.h"
#define BUFFER 1024

struct product {
char* code;
float price;
};

char* lookup_product(char* code) {
struct product products[] = {"ABCD", 50.00, "BCDE", 60.00};
size_t i;
for (i=0; i<sizeof(products)/ sizeof(struct product); i++) {
if (strcmp(code, products[i].code) == 0) {
return products[i].price;
}
}
return NULL;
}

char* not_found() {
return "<html><body>Product Not Found</body></html>\n";
}

void process(int fd) {
char buffer[BUFFER];
ssize_t bytes_read = read(fd, buffer, BUFFER);
if (bytes_read > 0) {
struct request* req = parse_request(buffer, bytes_read);
if (strcmp("GET",req->method) == 0 && strcmp("/price",req->path) == 0 && 
req->query_string != NULL) {
char* code = extract_product_code(req->query_string);
char* price = lookup_product(code);
if (price != NULL) {
send_response(fd, price, "text/html");
} else {
send_response(fd, not_found(), "text/html");
}
free_request(req);
} 
else {
send_bad_request(fd);
free_request(req);
}
}
close(fd);
}

int main() {
char buffer[BUFFER];
struct sockaddr_in addr;
socklen_t addrlen = sizeof(addr);
int fd;

int sfd = socket(AF_INET, SOCK_STREAM, 0);
if (sfd == -1) {
perror("socket");
exit(EXIT_FAILURE);
}
memset(&addr, 0, addrlen);
addr.sin_family = AF_INET;
addr.sin_port = htons(8080);
if (bind(sfd, (struct sockaddr*) &addr, addrlen) == -1) {
perror("bind");
exit(EXIT_FAILURE);
}

listen(sfd, 5);
while (1) {
fd = accept(sfd, (struct sockaddr *)&addr, &addrlen);
if (fd == -1) {
perror("accept");
continue;
}
process(fd);
}
close(sfd);
return 0;
}