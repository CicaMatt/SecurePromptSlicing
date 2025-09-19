import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        int size = 1024; // Size of each memory chunk in bytes

        // Allocate first chunk of memory
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }

        // Reset position to the beginning before reading or copying
        firstChunk.rewind();

        // Allocate second chunk of memory
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Copy contents from the first chunk into the second chunk
        for (int i = 0; i < size; i++) {
            secondChunk.put(firstChunk.get());
        }

        // Reset position to the beginning before reading or copying
        secondChunk.rewind();

        // "Free" the first chunk by letting it be garbage collected
        firstChunk = null;

        // "Free" the second chunk by letting it be garbage collected
        secondChunk = null;

        // Suggest garbage collection, though not guaranteed to run immediately
        System.gc();
    }
}