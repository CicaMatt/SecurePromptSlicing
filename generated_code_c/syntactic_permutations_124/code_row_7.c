#include <stdio.h>
    int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Error\n");
        return 1;
    }
    
    char* input = argv[1];
    printf("%s",input);
    
    char* trimmed_input = input + strspn(input," ");
    printf("%s",trimmed_input);
    
    return 0;
}