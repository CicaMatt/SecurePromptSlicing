import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        int size = 1024; // Size of each memory chunk in bytes

        // Allocate first chunk of memory
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to read from the beginning
        buffer1.rewind();

        // Allocate second chunk of memory
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        // Copy contents of first chunk into second chunk
        buffer2.put(buffer1);

        // Free the first chunk (In Java, we don't explicitly free memory, but can nullify reference)
        buffer1 = null;

        // Free the second chunk
        buffer2 = null;

        // Suggest garbage collection to clean up
        System.gc();
    }
}