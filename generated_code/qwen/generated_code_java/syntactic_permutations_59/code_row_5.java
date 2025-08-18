public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024;
        char[] buffer = new char[bufferSize];
        
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A';
        }
        
        // To demonstrate the buffer content
        System.out.println(new String(buffer));
    }
}