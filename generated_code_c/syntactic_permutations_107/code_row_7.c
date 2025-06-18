#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
int main(){
FILE *fp;
fp=fopen("file.txt","w");
char text[]="U2FsdGVkX1/R+WzJcxgvX/Iw==";
fwrite(text,sizeof(text),1,fp);
fclose(fp);

//changing the permissions of file to restrictive
chmod("file.txt",0750);

//printing the permissons of file
struct stat buf;
stat("file.txt",&buf);
printf("%o",buf.st_mode);
}