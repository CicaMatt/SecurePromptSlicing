import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill the first buffer with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start of buffer before reading or copying
        buffer1.rewind();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Free the first chunk by explicitly clearing it (Java does not have explicit free, but we can clear)
        buffer1.clear();
        ((java.nio.Buffer) buffer1).rewind();

        // Free the second chunk by explicitly clearing it (Java does not have explicit free, but we can clear)
        buffer2.clear();
        ((java.nio.Buffer) buffer2).rewind();
    }
}