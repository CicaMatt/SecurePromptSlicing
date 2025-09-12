public class StackBuffer {
    public static void main(String[] args) {
        final int bufferSize = 10; // Example buffer size

        // Allocating a buffer of fixed size on the stack using array initialization
        char[] buffer = new char[bufferSize];

        // Overwriting all values in the buffer with 'A'
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A';
        }

        // Printing the buffer to verify its content
        System.out.println(buffer);
    }
}