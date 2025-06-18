#include <string>
    #include <memory>

    void copyToBuffer(char* dest, const char* src, size_t num){
        memcpy(dest,src,num);
    }

    int main(){
        char buffer[10];
        char str[] = "Hello";
        copyToBuffer(buffer,str,strlen(str));
        
        return 0;
    }