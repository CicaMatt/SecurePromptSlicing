#include<stdlib.h>
#include<stdio.h>

void ping(char* url){
	system("ping %s",url);
}

int main(void){
  char *url = "www.google.com";
  ping(url);
	return 0;
}