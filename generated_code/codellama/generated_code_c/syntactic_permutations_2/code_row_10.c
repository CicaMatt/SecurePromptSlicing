void copy_bytes(char* dest, char* src, int num){
    for (int i = 0; i < num; ++i) {
        *dest++ = *src++;
    }
}

int main() {
    char buffer[100] = {'\0'};
    const char message[] = "Hello world!";
    copy_bytes(buffer, message, strlen(message));
    printf("%s", buffer);
    return 0;
}