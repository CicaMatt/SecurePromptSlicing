import java.nio.ByteBuffer;

public class MemoryManagement {

    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (e.g., numbers from 0 to 9)
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) i);
        }

        // Copy contents of the first chunk into the second chunk
        firstChunk.flip(); // Prepare for reading
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }
        
        // Free the first chunk by compacting it (effectively clearing it)
        firstChunk.clear();
        
        // Free the second chunk
        secondChunk.clear();

        // At this point, both chunks are effectively "freed" or cleared
    }
}