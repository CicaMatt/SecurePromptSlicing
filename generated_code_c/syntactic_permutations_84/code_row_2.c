#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <string.h> 

#define BUFFER_SIZE 1024 

typedef struct yaml { 
	char type[50]; //create or update 
	char name[50]; 
	int age; 
} yaml; 

void parse_yaml(char *buffer, struct yaml *user) { 
	//todo: parse the buffer using a YAML parser and populate user 
} 

int main() { 
	struct sockaddr_in server; 
	server.sin_family = AF_INET; 
	server.sin_port = htons(5000); 
	server.sin_addr.s_addr = INADDR_ANY; 

	int sfd, cfd; 
	sfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sfd == -1) { 
		perror("socket failed"); 
		exit(-1); 
	} 

	if (bind(sfd, (struct sockaddr *)&server, sizeof(server)) == -1) { 
		perror("bind failed"); 
		exit(-1); 
	} 

	if (listen(sfd, 5) == -1) { 
		perror("listen failed"); 
		exit(-1); 
	} 

	while (1) { 
		struct sockaddr_in client; 
		socklen_t len = sizeof(client); 
		char buffer[BUFFER_SIZE]; 

		cfd = accept(sfd, (struct sockaddr *)&client, &len); 
		if (cfd == -1) { 
			perror("accept failed"); 
			exit(-1); 
		} 

		read(cfd, buffer, BUFFER_SIZE); 

		struct yaml user; 
		parse_yaml(buffer, &user); 

		if (strcmp(user.type, "create") == 0) { 
			write(cfd, "error: cannot create", 25); 
		} else if (strcmp(user.type, "update") == 0) { 
			//todo: update user in database 
		} 

		close(cfd); 
	} 

	close(sfd); 

	return 0; 
}