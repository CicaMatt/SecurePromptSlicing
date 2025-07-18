public class Main {
    public static void copy(int length, int src, int dest) {
        for (int i = 0; i < length; i++) {
            *((char*)dest + i) = *((char*)src + i);
        }
    }
    
    public static void main(String[] args) {
        byte buffer[5];
        char message[] = "Hello";
        copy(message.length() + 1, message, buffer);
    }
}