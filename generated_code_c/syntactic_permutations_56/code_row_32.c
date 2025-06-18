#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>

#define PORT 8080
#define MAX_SIZE 100

struct userData{
	char email[MAX_SIZE];
	char newEmail[MAX_SIZE];
	char confirmPassword[MAX_SIZE];
	int loggedIn;
};

struct threadArgs{
	int clientSocket;
	struct sockaddr_in clientAddress;
	char buffer[2048];
	struct userData data;
};

void parseRequest(struct threadArgs *args);
void validateEmail(struct threadArgs *args, char* email);
void updateEmail(struct threadArgs *args);
void sendResponse(struct threadArgs *args);

int main()
{
	pthread_t tid;
	int serverSocket;
	struct sockaddr_in serverAddress;

	//Create socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		printf("Unable to create a socket\n");
	} else {
		printf("Socket successfully created\n");
	}

	//Define the server address
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(PORT);

	//Bind socket to port
	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

	//Listen on a port
	listen(serverSocket, 3);

	printf("Server is listening on port %d\n", PORT);

	while (1) {
		int clientSocket;
		struct sockaddr_in clientAddress;
		unsigned int clientLength = sizeof(clientAddress);

		//Accept connection from client
		clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientLength);
		if (clientSocket < 0) {
			printf("Failed to accept\n");
		} else {
			printf("Connection accepted from %s:%d\n", inet_ntoa(clientAddress.sin_addr), htons(clientAddress.sin_port));
		}

		//Create a thread for this client
		pthread_create(&tid, NULL, (void*)&parseRequest, &clientSocket);
		pthread_join(tid, NULL);
	}

	return 0;
}

void parseRequest(struct threadArgs *args)
{
	int clientSocket = args->clientSocket;

	//Receive request from client
	recv(clientSocket, &args->buffer, sizeof(args->buffer), 0);

	//Parse email and new email
	char* email = strstr(args->buffer, "email=");
	if (email != NULL) {
		int i;
		for (i = 0; i < MAX_SIZE; ++i) {
			args->data.email[i] = email[6 + i];
			if (email[6 + i] == '&') break;
		}
	}
	char* newEmail = strstr(args->buffer, "new-email=");
	if (newEmail != NULL) {
		int i;
		for (i = 0; i < MAX_SIZE; ++i) {
			args->data.newEmail[i] = newEmail[10 + i];
			if (newEmail[10 + i] == '&') break;
		}
	}

	//Parse confirm password
	char* confirmPassword = strstr(args->buffer, "confirm-password=");
	if (confirmPassword != NULL) {
		int i;
		for (i = 0; i < MAX_SIZE; ++i) {
			args->data.confirmPassword[i] = confirmPassword[17 + i];
			if (confirmPassword[17 + i] == '&') break;
		}
	}

	//Validate email address
	validateEmail(args, args->data.email);
	validateEmail(args, args->data.newEmail);

	updateEmail(args);

	sendResponse(args);

	close(clientSocket);
}

void validateEmail(struct threadArgs *args, char* email)
{
	//Check if the email address is valid
	if (email == NULL || strlen(email) < 6) {
		strcpy(args->buffer, "Invalid email address");
		return;
	}

	char* atSymbol = strchr(email, '@');
	if (atSymbol == NULL) {
		strcpy(args->buffer, "Invalid email address");
		return;
	}

	char* dotSymbol = strrchr(email, '.');
	if (dotSymbol == NULL || dotSymbol - atSymbol <= 1) {
		strcpy(args->buffer, "Invalid email address");
		return;
	}

	//Check if the email address already exists in the database
	FILE *fp = fopen("email.txt", "r");
	if (fp == NULL) {
		printf("Unable to open email.txt\n");
	} else {
		while (!feof(fp)) {
			char buffer[1024];
			fgets(buffer, 1024, fp);
			if (strcmp(email, buffer) == 0) {
				printf("Email already exists\n");
				strcpy(args->buffer, "Email already exists");
			}
		}
	}

	fclose(fp);
}

void updateEmail(struct threadArgs *args)
{
	//Check if the email and new email are different
	if (strcmp(args->data.email, args->data.newEmail) == 0) {
		printf("Email is already up-to-date\n");
		return;
	}

	//Update email address in database
	FILE *fp = fopen("email.txt", "w");
	if (fp == NULL) {
		printf("Unable to open email.txt\n");
		strcpy(args->buffer, "Failed to update email address");
	} else {
		fputs(args->data.newEmail, fp);
		fclose(fp);
		printf("Email updated successfully\n");
	}
}

void sendResponse(struct threadArgs *args)
{
	//Send response to client
	send(args->clientSocket, &args->buffer, strlen(args->buffer), 0);
}