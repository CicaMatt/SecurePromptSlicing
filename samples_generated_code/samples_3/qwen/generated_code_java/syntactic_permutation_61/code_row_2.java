import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        while (true) {
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            // Simulate some processing with the buffer
            buffer.clear(); // Clear the buffer for reuse or free it in terms of memory management
        }
    }
}