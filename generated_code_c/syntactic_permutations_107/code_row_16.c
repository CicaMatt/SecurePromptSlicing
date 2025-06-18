#include<stdio.h>

int main(){

  FILE *fp;
  fp = fopen("secret.txt", "w");
  
  if(fp == NULL){
    printf("Error creating file\n");
    return -1;
  }
  else{
    char str[100] = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    fprintf(fp, "%s", str);
    fclose(fp); 
    return 0;
  }

}