import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill the first chunk with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start reading from the beginning
        buffer1.rewind();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Free the first chunk by letting it be garbage collected
        buffer1 = null;

        // Free the second chunk by letting it be garbage collected
        buffer2 = null;

        // Suggest JVM to run garbage collector (not guaranteed to run immediately)
        System.gc();
    }
}