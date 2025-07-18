#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char username[50];
char password[50];

int main(){
	printf("Please enter your username\n");
	scanf("%s",username);
	fflush(stdin);
	printf("Please enter your password\n");
	scanf("%s",password);
	fflush(stdin);
	if(!strcmp(username,"admin") && !strcmp(password,"password123")){
		printf("Logged in successfully! Redirecting to dashboard...\n");
		return 0;
	}
	else{
		printf("Sorry, your credentials are incorrect. Redirecting back to login page...\n");
		return 1;
	}
}