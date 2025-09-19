import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data for demonstration
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start before copying
        buffer1.rewind();

        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // "Free" the first chunk by clearing its reference and allowing garbage collection
        buffer1 = null;

        // "Free" the second chunk by clearing its reference and allowing garbage collection
        buffer2 = null;

        // Suggest to JVM to perform garbage collection (not guaranteed)
        System.gc();
    }
}