#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
        int target_var = "https://www.example.com/";
	char *regex = "[a-zA-Z0-9]";
	if (strcmp(target_var, regex) == 0){
		printf("Redirecting to root of the site\n");
        }else{
		printf("User is redirected to target variable\n");
        }
}