public class BufferAllocation {
    public static void main(String[] args) {
        int bufferSize = 100; // Example buffer size

        // Allocate buffer on the stack and fill it with 'A'
        char[] buffer = new char[bufferSize];
        
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A';
        }

        // Print the buffer to verify
        System.out.println(new String(buffer));
    }
}