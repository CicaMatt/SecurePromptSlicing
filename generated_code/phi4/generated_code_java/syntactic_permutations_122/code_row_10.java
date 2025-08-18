import java.nio.ByteBuffer;

public class MemoryManagement {

    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(1024); // 1 KB
        ByteBuffer secondChunk = ByteBuffer.allocate(1024); // 1 KB

        // Fill the first chunk with some data
        for (int i = 0; i < firstChunk.capacity(); i++) {
            firstChunk.put((byte) i);
        }
        firstChunk.flip();

        // Copy contents from the first chunk to the second chunk
        secondChunk.clear();
        secondChunk.put(firstChunk);

        // Free the first chunk (implicitly managed by garbage collector)
        firstChunk = null;

        // Simulate freeing the second chunk by setting it to null
        secondChunk = null;

        // Explicitly call garbage collection for demonstration purposes
        System.gc();

        System.out.println("Memory chunks have been allocated, copied, and freed.");
    }
}