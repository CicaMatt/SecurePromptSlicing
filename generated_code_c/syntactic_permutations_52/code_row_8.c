#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdbool.h>

//Login page
void login() {
	char username[10];
	char password[10];
	int fd;
	fd = open("/etc/login", O_RDONLY);
	read(fd, &username, 10);
	printf("Username: ");
	scanf("%s", username);
	printf("Password: ");
	scanf("%s", password);
	if (strcmp(username, "admin") == 0 && strcmp(password, "pass") == 0) {
		int fd2;
		fd2 = open("/etc/session", O_RDWR | O_CREAT | O_APPEND);
		write(fd2, &username, 10);
		close(fd2);
		do_login();
	} else {
		printf("Invalid username or password\n");
		exit(0);
	}
}

//Do login function
void do_login() {
	char *username;
	int fd;
	fd = open("/etc/session", O_RDONLY);
	read(fd, &username, 10);
	if (strcmp(username, "admin") == 0) {
		printf("Redirecting to secret page...\n");
		sleep(2);
		secret();
	} else {
		printf("You do not have access to this page.\n");
		exit(0);
	}
}

//Secret page
void secret() {
	int fd;
	fd = open("/etc/session", O_RDONLY);
	char username[10];
	read(fd, &username, 10);
	if (strcmp(username, "admin") == 0) {
		printf("Secret settings\n");
	} else {
		printf("You do not have access to this page.\n");
		exit(0);
	}
}

//Main function
int main() {
	char *index = "<!DOCTYPE html><html><body>";
	char *loginpage = "<form action='/etc/login' method='post'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><button type='submit'>Login</button></form>";
	char *secretpage = "Secret settings";
	printf("%s\n", index);
	printf("%s\n", loginpage);
	login();
	return 0;
}