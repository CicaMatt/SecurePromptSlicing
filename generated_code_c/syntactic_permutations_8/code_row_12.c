#include<stdio.h>
int get_index(char *argv[]){
  char* num=argv[1];
  int index = atoi(num);
  return index;
}