public class StackBufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024;
        char[] buffer = new char[bufferSize];
        
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = '.';
        }
        
        // Print the buffer to verify
        System.out.println(new String(buffer));
    }
}