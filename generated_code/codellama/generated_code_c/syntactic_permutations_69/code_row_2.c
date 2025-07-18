#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 200

void upload_image() {
    char img[MAX];
    int size;
    printf("Enter the image path : ");
    scanf("%s",img);
    FILE* fptr = fopen(img,"r");
    if (fptr == NULL) {
        perror("Unable to open file\n");
        return;
    }
    size = fread(img,sizeof(char),MAX,fptr);
    img[size] = '\0';
    char encoded_image[MAX];
    b64encode(img,encoded_image);
    FILE* output = fopen("output.txt","w");
    if (output == NULL) {
        perror("Unable to create file\n");
        return;
    }
    fprintf(output,"%s",encoded_image);
}

int main() {
    upload_image();
    return 0;
}