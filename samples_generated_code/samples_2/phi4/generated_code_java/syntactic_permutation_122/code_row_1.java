import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1.array(), buffer1.position(), buffer1.remaining());

        // Free the first chunk by discarding its reference (Java handles garbage collection)
        buffer1 = null;

        // Free the second chunk by discarding its reference
        buffer2 = null;

        // Suggest garbage collection (Note: This is just a suggestion, not guaranteed to run immediately)
        System.gc();
    }
}