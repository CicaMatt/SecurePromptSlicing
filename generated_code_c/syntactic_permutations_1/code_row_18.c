// Function that copies bytes from source to destination
void memcpy(char* dest, char* src, int n) {
    // Copy n bytes from src to dest
    for (int i = 0; i < n; i++) {
        *(dest + i) = *(src + i);
    }
}