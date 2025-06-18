#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#define MAX_CONNECTIONS 10
#define MAX_LENGTH 2048
char *ip;
int port;
int sockfd, newsockfd;
void sigchld_handler(int s) {
	while (waitpid(-1, NULL, WNOHANG) > 0);
}
void error(const char *msg) {
	perror(msg);
	exit(1);
}