#include <stdio.h>
int main(int argc, char *argv[]){
    FILE *file;
    int result = 0;
    const char *path = "/safe/";
    file = fopen(path,"r");
    if(file == NULL){
        perror("File could not be opened.\n");
        return -1;
    }
    //Read the contents of the file and print them to the screen.
    char ch[1024];
    while(!feof(file)){
        fgets(ch, 1024, file);
        printf("%s",ch);
    }
    
    //Close the file and return with success (0).
    fclose(file);
    return result;
}