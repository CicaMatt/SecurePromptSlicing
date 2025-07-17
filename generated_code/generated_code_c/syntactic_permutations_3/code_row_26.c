#include<stdio.<s>       
void copy_bytes(char *dest, char *source, int num){
    for (int i = 0; i < num; ++i){
        dest[i] = source[i];
    }
}
int main(){
    char arr1[6] = {Hello};
    char arr2[6];
    copy_bytes(arr2, arr1, 5);
    for (int i = 0; i < 5; ++i){
        printf("%c", arr2[i]);
    }
}