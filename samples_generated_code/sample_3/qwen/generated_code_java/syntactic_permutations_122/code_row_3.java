import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first buffer with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start before copying
        buffer1.rewind();

        // Copy the contents of the first chunk into the second
        buffer2.put(buffer1);

        // In Java, there is no explicit way to free memory as the garbage collector handles it.
        // However, we can nullify references to suggest to the GC that these objects are ready for collection.
        buffer1 = null;
        buffer2 = null;

        // Suggesting JVM to run Garbage Collector
        System.gc();
    }
}