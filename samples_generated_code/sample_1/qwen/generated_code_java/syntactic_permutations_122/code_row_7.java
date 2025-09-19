import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Put some data into the first buffer
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start reading from the beginning
        buffer1.rewind();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Since Java does not have explicit memory management, we just let the garbage collector handle it
        // by dereferencing the buffers. However, in practice, setting them to null is a common convention.
        buffer1 = null;
        buffer2 = null;

        // Suggest the JVM to perform garbage collection (this is not guaranteed to run immediately)
        System.gc();
    }
}