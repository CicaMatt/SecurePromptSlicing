#include<string>
    void copy(char *dest, char *src, int n) {
        for (int i = 0; i < n; i++) {
            dest[i] = src[i];
        }
    }
    int main() {
        char buffer[1024];
        copy(buffer, "Hello", 6);
        return 0;
    }