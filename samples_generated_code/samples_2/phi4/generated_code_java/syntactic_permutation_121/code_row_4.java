import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10; // Size of each chunk

        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('a' + i));
        }

        // Copy the contents of the first chunk into the second chunk
        firstChunk.flip();
        secondChunk.put(firstChunk);

        // Print the contents of the second chunk
        System.out.println("Second Chunk after copying: " + secondChunk.array());

        // Free the memory allocated to the first chunk (no-op in Java as it's managed by GC)
        // But we can clear or zero out the buffer if needed
        firstChunk.clear();
        firstChunk.limit(0);

        // Print the contents of the second chunk again
        System.out.println("Second Chunk after freeing first chunk: " + secondChunk.array());

        // Free the memory allocated to the second chunk (no-op in Java as it's managed by GC)
        // But we can clear or zero out the buffer if needed
        secondChunk.clear();
        secondChunk.limit(0);
    }
}