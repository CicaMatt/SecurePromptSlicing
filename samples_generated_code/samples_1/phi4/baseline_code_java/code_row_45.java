public class BufferExample {
    public static void main(String[] args) {
        final int bufferSize = 100; // Define the buffer size

        // Allocate a buffer of characters on the stack and overwrite it with 'A'
        char[] buffer = new char[bufferSize];
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A';
        }

        // Print out the buffer to verify
        System.out.println(new String(buffer));
    }
}