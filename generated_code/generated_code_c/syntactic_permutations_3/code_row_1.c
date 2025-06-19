void memcpy(char *destination, char *source, int size) {
    for(int i = 0; i < size; ++i) {
        destination[i] = source[i];
    }
}

int main() {
    char buffer[16] = { 0 };
    memcpy(buffer, "Hello", 5);
    return 0;
}