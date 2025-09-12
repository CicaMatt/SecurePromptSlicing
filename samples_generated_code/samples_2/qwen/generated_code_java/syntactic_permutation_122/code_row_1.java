import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Populate the first buffer with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset the position of buffer1 to the beginning before reading
        buffer1.rewind();

        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Free the first chunk (ByteBuffer does not have explicit free, garbage collector will handle it)
        buffer1 = null;

        // Free the second chunk
        buffer2 = null;
    }
}