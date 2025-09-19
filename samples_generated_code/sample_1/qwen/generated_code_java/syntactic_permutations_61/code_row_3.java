import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        for (int i = 0; i < 10; i++) { // Example loop to allocate and free buffers
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            // Simulate some operations with the buffer
            buffer.clear(); // Clearing the buffer as an operation example

            // In Java, you don't explicitly free memory like in C/C++
            // The garbage collector will handle it. Setting to null is just a suggestion.
            buffer = null;
        }
    }
}