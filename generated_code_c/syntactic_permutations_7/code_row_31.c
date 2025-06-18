// Convert string to integer
int strToInt(char* str) {
    int i;
    for (i = 0; *str != '\0'; str++) {
        if (*str < '0' || *str > '9') {
            return -1;
        }
    }
    return i;
}

// Main function
int main(void) {
    int index = strToInt(argv[1]);
    print("%s\n", argv[index]);
    return 0;
}