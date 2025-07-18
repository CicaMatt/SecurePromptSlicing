#include <stdio.h>
    int main(){
     FILE *fp;
     char buff[512];
     size_t nbytes;
     fp = fopen("file.txt","r");
     if (f == NULL){
         printf("Could not open file\n");
         return 0;
     }
     nbytes = fread(buff,sizeof(char),512,fp);
     if (nbytes == 0){
         printf("File is empty\n");
         return 0;
     }
     fclose(fp);
     FILE *fp1;
     fp1 = fopen("out.txt","w");
     if (fp1 == NULL){
         printf("Could not create output file\n");
         return 0;
     }
     fwrite(&nbytes,sizeof(size_t),1,fp1);
     fclose(fp1);
     return 0;
    }