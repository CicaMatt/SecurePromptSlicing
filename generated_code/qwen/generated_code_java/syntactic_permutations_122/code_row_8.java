import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 1024; // Size of the memory chunk in bytes
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }

        // Reset position to start reading from the beginning
        firstChunk.flip();

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Free the first chunk by clearing its reference and allowing garbage collection
        firstChunk = null;

        // Free the second chunk by clearing its reference and allowing garbage collection
        secondChunk = null;

        // Suggest to JVM that it can perform garbage collection
        System.gc();
    }
}