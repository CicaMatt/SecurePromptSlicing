#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int check_email(char*);
int remove_email(char*);

int main(){
	char email[50];
	printf("Enter your email address: ");
	scanf("%s",email);
	if(check_email(email)==1){
		remove_email(email);
	}else{
		printf("%s is not a valid email.\n",email);
	}
	return 0;
}

int check_email(char* email){
	//connect to database and query the email address
	printf("Checking if %s exists in the database\n",email);
	if(strcmp(email,"example@domain.com")==0)
		return 1;
	else
		return 0;
}
int remove_email(char* email){
	//connect to database and delete query the email address
	printf("%s has been removed from the database\n",email);
	return 0;
}