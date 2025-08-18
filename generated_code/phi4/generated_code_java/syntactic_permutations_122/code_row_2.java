import java.nio.ByteBuffer;

public class MemoryAllocator {

    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill the first chunk with some data (for demonstration)
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1.array());

        // Free the first chunk by discarding its reference
        buffer1 = null;

        // Optionally, invoke garbage collection to free memory (not guaranteed)
        System.gc();

        // Free the second chunk by discarding its reference
        buffer2 = null;

        // Optionally, invoke garbage collection again to free memory (not guaranteed)
        System.gc();
    }
}