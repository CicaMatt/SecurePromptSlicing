import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill the first chunk with some data (for demonstration purposes)
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }
        
        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1.array());

        // Free the first chunk by discarding its reference
        buffer1 = null;
        
        // Suggest garbage collection (not guaranteed to run immediately)
        System.gc();

        // Free the second chunk by discarding its reference
        buffer2 = null;

        // Suggest garbage collection again
        System.gc();
    }
}