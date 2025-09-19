import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        for (int i = 0; i < 10; i++) { // Loop 10 times
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize); // Allocate buffer
            // Perform operations with the buffer if necessary
            buffer.clear(); // Clear the buffer for reuse or free resources
        }
    }
}