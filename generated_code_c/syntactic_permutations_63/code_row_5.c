#include<stdio.h>
#include<stdlib.h>
int main(){
    int ch;
    unsigned char data[1024];
    FILE* fp=fopen("data.txt","r");
    if(fp==NULL){
        return 0;
    }
    int i=0;
    while((ch=fgetc(fp))!=EOF){
        data[i]=ch;
        i++;
    }
    fclose(fp);
    unsigned char checksum=data[i-1];
    if(checksum==0){
        printf("Buffer is empty\n");
    }else{
        printf("Checksum: %d",checksum);
        FILE* fp2=fopen("result.txt","w");
        int bytes_read=i-1;
        fprintf(fp2,"%d %d",bytes_read,checksum);
    }
}