public class StackBufferExample {

    public static void main(String[] args) {
        int bufferSize = 10; // Define your buffer size here

        char[] buffer = new char[bufferSize]; // Allocate buffer on the stack (as part of method stack frame)

        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A'; // Overwrite all values with 'A'
        }

        System.out.println(new String(buffer)); // Print the buffer to verify
    }
}