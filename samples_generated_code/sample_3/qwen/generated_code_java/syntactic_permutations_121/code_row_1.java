import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10;
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('A' + i));
        }

        // Reset position to start before copying
        firstChunk.rewind();

        // Copy the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Reset position to start for reading
        secondChunk.rewind();

        // Print the second chunk
        System.out.print("Second chunk after copy: ");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Clear the first chunk (freeing its memory)
        firstChunk.clear();

        // Reset position to start for reading
        secondChunk.rewind();

        // Print the second chunk again
        System.out.print("Second chunk after clearing first: ");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Clear the second chunk (freeing its memory)
        secondChunk.clear();
    }
}