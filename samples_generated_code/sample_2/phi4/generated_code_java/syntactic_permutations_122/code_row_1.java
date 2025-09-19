import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 1024; // Example size, can be adjusted
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with example data (e.g., all bytes set to 1)
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) 1);
        }
        firstChunk.flip(); // Prepare for reading

        // Copy contents from the first chunk to the second chunk
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }

        // Free the first chunk by clearing it (in Java, this is just done by going out of scope)
        firstChunk.clear();
        
        // Free the second chunk by clearing it (in Java, this is also managed by garbage collection)
        secondChunk.clear();
    }
}