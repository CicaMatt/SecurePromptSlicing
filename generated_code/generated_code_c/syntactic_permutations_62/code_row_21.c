#include <stdio.h>
#include <stdlib.h>
int main(void){
    FILE *fp;
    char buffer[1024];
    size_t bytesRead, sum = 0;
    fp=fopen("file.txt","r");
    if(fp==NULL)return -1;
    while((bytesRead=fread(buffer,sizeof(char),1024,fp))>0){
        for(int i=0;i<bytesRead;i++){
            sum+=buffer[i];
        }
    }
    fclose(fp);
    return (sum==0)?0:-1;
}