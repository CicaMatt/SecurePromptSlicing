import java.nio.ByteBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        int size = 1024; // Size of each memory chunk

        // Allocate first chunk of memory
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Allocate second chunk of memory
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        // Reset position to start before copying
        buffer1.rewind();

        // Copy contents from first chunk to second chunk
        buffer2.put(buffer1);

        // Free the first chunk (in Java, we don't explicitly free memory,
        // but we can nullify the reference and rely on garbage collector)
        buffer1 = null;

        // Free the second chunk
        buffer2 = null;
    }
}