import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }
        buffer1.flip(); // Prepare buffer1 for reading

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Free the first chunk by discarding its reference (handled by GC)
        buffer1 = null;

        // Free the second chunk by discarding its reference (handled by GC)
        buffer2 = null;
        
        // Suggest garbage collection for demonstration purposes only
        System.gc();
    }
}