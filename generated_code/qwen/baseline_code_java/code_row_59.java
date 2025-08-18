public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        char[] buffer = new char[bufferSize];
        
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A';
        }
        
        // Print the first 10 characters to verify
        for (int i = 0; i < 10; i++) {
            System.out.print(buffer[i]);
        }
    }
}