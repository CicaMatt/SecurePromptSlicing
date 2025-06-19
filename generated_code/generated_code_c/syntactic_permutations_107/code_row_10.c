#include<stdio.h>
    int main(){
    FILE *file;
    file = fopen("secret.txt","w");  //creating a new file and opening it in write mode
    char str[]="This is a secret file";  //writing to the file
    fprintf(file,"%s",str);
    fclose(file);   //closing the file
    chmod("secret.txt",0644);  //changing permissions to restrictive
    int permission = getmode("secret.txt");
    printf("%d",permission);
    return 0;
    }