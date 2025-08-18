import java.nio.ByteBuffer;

public class MemoryAllocation {

    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (e.g., numbers 0 to 9)
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }
        
        // Reset position of buffer1 to read from it
        buffer1.flip();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Free the first chunk by discarding its reference (handled automatically by GC)
        buffer1 = null;

        // Free the second chunk by discarding its reference (handled automatically by GC)
        buffer2 = null;

        // Suggest garbage collection, though it's not guaranteed to run immediately
        System.gc();
    }
}