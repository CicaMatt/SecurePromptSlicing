import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill the first buffer with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start of buffer before copying
        buffer1.rewind();

        // Copy contents of the first buffer to the second buffer
        buffer2.put(buffer1);

        // Free the first buffer by setting it to null and calling gc
        buffer1 = null;
        System.gc();

        // Free the second buffer by setting it to null and calling gc
        buffer2 = null;
        System.gc();
    }
}