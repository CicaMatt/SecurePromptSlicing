#include <stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char*argv[]){
  if (argc<2){
    printf("Error: No command line arguments\n");
    exit(0);
  }
  int i;
  for(i=1;i<argc;i++){
    int len=strlen(argv[i]);
    while(argv[i][len-1]==' '||argv[i][len-1]=='\t'){
      argv[i][len-1]='\0';
      len--;
    }
  printf("%s\n",argv[i]);
  return 0;
  }