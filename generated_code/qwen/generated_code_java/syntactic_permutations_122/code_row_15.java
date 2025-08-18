import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill the first buffer with some data (for demonstration purposes)
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset the position of buffer1 to the beginning before reading
        buffer1.rewind();

        // Copy the contents from buffer1 to buffer2
        buffer2.put(buffer1);

        // Free the first chunk (In Java, we don't explicitly free memory,
        // but we can help the garbage collector by setting references to null)
        buffer1 = null;

        // Free the second chunk
        buffer2 = null;

        // Suggest to the JVM that it could run garbage collection
        System.gc();
    }
}