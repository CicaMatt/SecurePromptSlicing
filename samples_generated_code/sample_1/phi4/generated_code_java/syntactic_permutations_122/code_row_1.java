import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (buffers)
        ByteBuffer buffer1 = ByteBuffer.allocate(1024);
        ByteBuffer buffer2 = ByteBuffer.allocate(1024);

        // Fill the first chunk with some data
        for (int i = 0; i < buffer1.limit(); i++) {
            buffer1.put((byte) i);
        }

        // Reset position to read from the beginning
        buffer1.flip();

        // Copy contents of the first chunk into the second chunk
        buffer2.clear();
        buffer2.put(buffer1);

        // Freeing memory by discarding references (handled automatically in Java)
        
        // Buffer 1 is no longer needed
        buffer1 = null;

        // Buffer 2 will be freed when it goes out of scope or explicitly set to null
        buffer2 = null;
    }
}