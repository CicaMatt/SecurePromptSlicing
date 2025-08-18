import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 1024; // Size of each memory chunk in bytes
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data (for demonstration, we'll use simple numbers)
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i % 256); // Put values from 0 to 255 repeatedly
        }
        
        // Reset position to start of the buffer before reading or copying
        firstChunk.flip();

        // Copy contents from the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Free (deallocate) the first chunk by letting it go out of scope
        // In Java, memory management is handled automatically via garbage collection
        // So no explicit freeing code is needed

        // To mimic "freeing" the second chunk manually, we set the reference to null
        secondChunk = null;

        // Suggest garbage collection (not guaranteed)
        System.gc();
    }
}