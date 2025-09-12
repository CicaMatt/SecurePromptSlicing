import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        for (int i = 0; i < 10; i++) { // Example loop to allocate and free the buffer
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            // Simulate some operations with the buffer
            buffer.clear(); // Clearing the buffer as a placeholder operation
            // No explicit freeing in Java, garbage collector handles it
        }
    }
}