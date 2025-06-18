#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, char*argv[]){
  int id_status;
  if (argc <2){
     printf("please enter a username");
      return 1;
    }
   if((id_status = system( "id",argv[1])) !=0){
     printf("error: command failed with exit status %d\n",id_status);
     return id_status;
   }
   return 0;
}