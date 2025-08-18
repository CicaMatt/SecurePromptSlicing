public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024;
        char[] buffer = new char[bufferSize];
        
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A';
        }
        
        // Print the first 10 characters to verify
        System.out.println(String.valueOf(buffer, 0, 10));
    }
}