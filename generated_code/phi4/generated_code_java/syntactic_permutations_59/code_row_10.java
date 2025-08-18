public class BufferAllocation {

    public static void main(String[] args) {
        final int bufferSize = 10; // Example buffer size

        // Allocate and overwrite buffer on the stack using array
        char[] buffer = new char[bufferSize];
        
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A';
        }

        // Print the buffer to verify contents
        System.out.println(buffer);
    }
}