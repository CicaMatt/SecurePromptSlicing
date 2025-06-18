void copy(char *dest, char *src, int num) {
    for (int i = 0; i < num; i++) {
        *(dest + i) = *(src + i);
    }
}

int main() {
   char src[5] = "Hello";
   char dest[26];
   copy(dest, src, 4);
}