import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill the first buffer with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }
        buffer1.flip(); // Prepare to read from the buffer

        // Copy contents of buffer1 into buffer2
        buffer2.put(buffer1);

        // "Free" the first chunk by clearing its reference and allowing garbage collection
        buffer1 = null;

        // "Free" the second chunk by clearing its reference and allowing garbage collection
        buffer2 = null;

        // Suggest to JVM to perform garbage collection (not guaranteed)
        System.gc();
    }
}