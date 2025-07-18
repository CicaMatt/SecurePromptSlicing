void strCopy(char* dest, char const *src, int nb) { 
    while (nb > 0) { 
        *dest++ = *src++; 
        --nb; 
    } 
} 

int main() { 
    char buffer[16]; 
    strCopy(buffer, "Hello", strlen("Hello")); 
    // prints "Hello" 
    printf("%s\n", buffer); 
    return 0; 
}