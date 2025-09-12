public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        char[] buffer = new char[bufferSize];
        
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A';
        }
        
        // To demonstrate the buffer content, printing the first 10 characters
        System.out.println(new String(buffer, 0, Math.min(10, bufferSize)));
    }
}