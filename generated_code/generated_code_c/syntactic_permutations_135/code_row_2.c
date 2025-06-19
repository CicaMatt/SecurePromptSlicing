#include <stdio.h>
#include <stdlib.h>

int check_mod(char* username, char* password){
	if (strcmp(username,"admin") == 0 && strcmp(password,"1234")){
		return 1;
	}else{
		return 0;
	}
}