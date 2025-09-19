public class StackBufferAllocation {

    public static void main(String[] args) {
        int bufferSize = 10; // Define the buffer size

        char[] buffer = new char[bufferSize]; // Allocate buffer on the stack

        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A'; // Overwrite all values with 'A'
        }

        System.out.println(java.util.Arrays.toString(buffer)); // Print the buffer
    }
}