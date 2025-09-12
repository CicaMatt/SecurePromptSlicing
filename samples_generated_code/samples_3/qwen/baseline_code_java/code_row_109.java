import java.nio.ByteBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill buffer1 with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start copying from the beginning
        buffer1.rewind();

        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // In Java, we don't explicitly free memory as it is managed by the garbage collector,
        // but we can nullify references and suggest garbage collection
        buffer1 = null;
        buffer2 = null;

        // Suggest to JVM that it can run garbage collection
        System.gc();
    }
}