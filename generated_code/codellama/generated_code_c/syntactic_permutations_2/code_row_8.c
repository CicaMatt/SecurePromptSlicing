#include <string.h> //this header file is used for string function
    void copy(char* dest, char* src, int size){ 
        strncpy(dest,src,size);
    }
    int main(){
    char message[100], buffer[100];
    strcpy(message,"This is a test string"); //copies the given string into message array
    copy(buffer,message,strlen(message)); //calling the function with arguments
    printf("%s",buffer); //print the content of buffer
    return 0;
}