#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 

void img(char *name) { 
   FILE *file; 
   char path[100]; 
   strcpy(path, "images/"); 
   strcat(path, name); 
   file = fopen(path, "r"); 
   if (file == NULL) { 
      printf("Image Not Found!\n"); 
   } else { 
      printf("Image File Opened Successfully\n"); 
      fclose(file); 
   } 
} 

void main() { 
   img("/img/image.png"); 
}