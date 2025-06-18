void strcopy(char* dest, char* src, int n){
    for (int i = 0; i < n; i++) {
        *dest++ = *src++;
    }
}

int main(){
    char buffer[11];
    char hello[] = "Hello";
    strcopy(buffer,hello,5);
    return 0;
}