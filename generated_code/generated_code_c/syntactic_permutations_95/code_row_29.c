#include <stdio.h>

int main(void) 
{
	char username[256];
	printf("Enter your username: ");
	scanf("%s",username);
	
	char password[256];
	printf("Enter your password: ");
	scanf("%s",password); 
	
	//hashed the password and store it in hash variable
	int hash = 0;
	for(int i=0;i<strlen(password);i++)
	{
		hash += (password[i] * (i+1));
	}
	
	//generate a random salt and store it in salt variable
	char salt[4];
	srand((int)time(0));
	for(int i=0;i<3;i++)
	{
		salt[i] = rand()%10;
	}
	
	//append the hash and salt into one string called stored_pass
	char stored_password[256];
	strcpy(stored_password,password);
	strcat(stored_password,salt); 
	
	//store the username and password in database
	FILE *f;
	f = fopen("database.txt","w");
	fprintf(f,"%s",username);
	fprintf(f,"\n");
	fprintf(f,"%s",stored_password);
	fclose(f);
	
	return 0;
}