import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 1024; // Size of each memory chunk

        // Allocate first chunk of memory
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }

        // Reset position to start reading from the beginning
        firstChunk.rewind();

        // Allocate second chunk of memory
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Copy contents from first chunk to second chunk
        secondChunk.put(firstChunk);

        // Free the first chunk (in Java, we don't explicitly free memory,
        // but we can make it eligible for garbage collection)
        firstChunk = null;

        // Free the second chunk
        secondChunk = null;

        // Suggest to JVM to perform garbage collection
        System.gc();
    }
}