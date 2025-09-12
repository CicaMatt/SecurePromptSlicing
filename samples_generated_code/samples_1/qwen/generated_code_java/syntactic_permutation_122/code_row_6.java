import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Populate the first buffer with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset buffer position to start before copying
        buffer1.rewind();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Free the first chunk by setting its reference to null and calling garbage collector
        buffer1 = null;
        System.gc();

        // Free the second chunk by setting its reference to null and calling garbage collector
        buffer2 = null;
        System.gc();
    }
}