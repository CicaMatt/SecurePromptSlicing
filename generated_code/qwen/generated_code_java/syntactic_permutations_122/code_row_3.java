import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Populate buffer1 with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset the position of buffer1 to read from the beginning
        buffer1.rewind();

        // Copy the contents of buffer1 into buffer2
        buffer2.put(buffer1);

        // In Java, there's no explicit free operation for ByteBuffer.
        // The garbage collector will automatically reclaim the memory when the buffers are no longer in use.
        // However, we can help the GC by explicitly setting them to null and calling System.gc()
        buffer1 = null;
        buffer2 = null;

        // Suggesting JVM to perform garbage collection
        System.gc();
    }
}