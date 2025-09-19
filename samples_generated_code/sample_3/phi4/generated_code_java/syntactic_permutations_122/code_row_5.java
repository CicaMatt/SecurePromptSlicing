import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate the first chunk of memory (size 10)
        ByteBuffer firstChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) i);
        }

        // Allocate the second chunk of memory (size 10)
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Copy contents from the first chunk to the second chunk
        firstChunk.flip(); // Prepare for reading
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }

        // Free the first chunk by letting it go out of scope
        firstChunk = null;

        // Simulate garbage collection (in real scenarios, this is managed automatically)
        System.gc();

        // Free the second chunk by letting it go out of scope
        secondChunk = null;

        // Simulate garbage collection again
        System.gc();
    }
}