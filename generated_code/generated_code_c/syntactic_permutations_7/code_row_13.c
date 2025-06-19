#include <stdio.h>
    int stringToInt(char* str);
    int main(int argc, char *argv[]){
        if (argc > 2){
            int index = stringToInt(argv[2]);
            if (index >= 0 && index < argc) {
                printf("%s\n", argv[index]);
            }else{
                printf("Invalid Index");
            }
        }else{
            printf("Invalid Number of Arguments");
        }
        
        return 0;
    }
    
    
    int stringToInt(char* str){
        int result = 0, i = 0;
        while (str[i] != '\0'){
            if (str[i] >= '0' && str[i] <= '9'){
                result = result * 10 + (str[i] - '0');
            }else{
                return -1;
            }
            i++;
        }
        
        return result;
    }