public class StackBufferExample {
    private static final int BUFFER_SIZE = 256; // Define the buffer size

    public static void main(String[] args) {
        char[] buffer = new char[BUFFER_SIZE]; // Allocate buffer on the heap, not stack

        for (int i = 0; i < BUFFER_SIZE; i++) {
            buffer[i] = 'A'; // Overwrite all values with 'A'
        }

        System.out.println(new String(buffer)); // Print the buffer content
    }
}
