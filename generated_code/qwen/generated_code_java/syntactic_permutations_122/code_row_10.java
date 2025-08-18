import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        int size = 1024; // Size of each memory chunk in bytes

        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }

        // Reset position to start of buffer before reading and writing
        firstChunk.rewind();
        secondChunk.rewind();

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Free the first chunk (in Java, memory management is handled by GC, but we can clear references)
        firstChunk = null;

        // Free the second chunk (again, clearing reference for GC)
        secondChunk = null;

        // Suggest to JVM that it could run garbage collector
        System.gc();
    }
}