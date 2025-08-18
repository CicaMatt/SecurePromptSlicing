import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes.
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with example data (e.g., numbers from 0 to 9).
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Copy contents of the first chunk into the second chunk.
        buffer2.put(buffer1.array(), 0, buffer1.limit());

        // Free the first chunk by discarding its reference (Java handles garbage collection).
        buffer1 = null;

        // Free the second chunk by discarding its reference (Java handles garbage collection).
        buffer2 = null;

        // Suggest to JVM that it is a good time for garbage collection.
        System.gc();
    }
}