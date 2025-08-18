public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        char[] buffer = new char[bufferSize];
        
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A';
        }
        
        // To demonstrate the buffer content, we print it
        System.out.println(new String(buffer));
    }
}