void memcpy(char* dest, char* src, int n) {
    for (int i = 0; i < n; i++) {
        *dest++ = *src++;
    }
}

int main() {
    char* source = "Hello World";
    char* destination = "";
    memcpy(destination, source, 12);
    printf("%s", destination);
    return 0;
}