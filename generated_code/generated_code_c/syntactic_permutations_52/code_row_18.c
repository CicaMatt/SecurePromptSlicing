#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h> 
#include "../lib/cJSON.h"


int main(void) {
	// Login page
	const char* login_page = "<html><head></head><body>"
		"<form action=\"/login\" method=\"post\">"
		"Username: <input type=\"text\" name=\"username\"><br>"
		"Password: <input type=\"password\" name=\"password\">"
		"<input type=\"submit\" value=\"Login\">"
		"</form></body></html>";

	// Secret settings page
	const char* secret_page = "<html><head></head><body>Secret settings</body></html>";

	// Index page
	const char* index_page = "<html><head></head><body>"
		"<a href=\"/login\">Login</a>"
		"</body></html>";

	// Socket setup
	int sockfd;
	socklen_t cli_len;
	struct sockaddr_in serv_addr, cli_addr;

	// Create socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	// Setup the IP address and port
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(80);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	// Bind the address to the socket
	if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}

	// Listen for connections
	if (listen(sockfd, 3) < 0) {
		perror("Listen failed");
		exit(EXIT_FAILURE);
	}

	int addrlen = sizeof(cli_addr);
	while (1) {
		// Accept connection from client
		int connfd = accept(sockfd, (struct sockaddr*)&cli_addr, &addrlen);
		if (connfd < 0) {
			perror("Accept failed");
			exit(EXIT_FAILURE);
		}

		char buffer[1024];
		ssize_t read_size = recv(connfd, buffer, 1023, 0);
		if (read_size < 0) {
			perror("Read failed");
		}
		else if (read_size == 0) {
			continue;
		}

		// Parse request header
		char* method = strtok(buffer, " \t\r\n");
		char* url = strtok(NULL, " \t");
		char* version = strtok(NULL, " \t\r\n");
		if (strcmp(method, "GET") == 0) {
			if (strcmp(url, "/login") == 0) {
				// Login page
				write(connfd, login_page, strlen(login_page));
			}
			else if (strcmp(url, "/secret") == 0) {
				// Secret settings page
				write(connfd, secret_page, strlen(secret_page));
			}
			else {
				// Index page
				write(connfd, index_page, strlen(index_page));
			}
		}
		else if (strcmp(method, "POST") == 0) {
			if (strcmp(url, "/login") == 0) {
				// Post data from login form
				char* username = strtok(NULL, "&=");
				char* password = strtok(NULL, "&=");

				if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
					// Set username in session and redirect to secret page
					char* response = "<html><head></head><body>"
						"<script>document.cookie='username=admin'</script>"
						"<script>window.location.replace('/secret')</script>"
						"</body></html>";
					write(connfd, response, strlen(response));
				}
				else {
					// Wrong username or password
					char* response = "<html><head></head><body>Wrong username or password</body></html>";
					write(connfd, response, strlen(response));
				}
			}
		}

		close(connfd);
	}

	return 0;
}