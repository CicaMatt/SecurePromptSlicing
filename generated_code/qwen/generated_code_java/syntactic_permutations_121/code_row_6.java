import java.nio.ByteBuffer;

public class MemoryChunkExample {
    public static void main(String[] args) {
        int size = 10;
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('A' + i));
        }

        // Reset position to copy from start
        firstChunk.rewind();

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Reset position for reading
        secondChunk.rewind();

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying:");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Clear first chunk, simulating freeing memory
        firstChunk.clear();

        // Reset position for reading again
        secondChunk.rewind();

        // Print the contents of the second chunk after clearing the first
        System.out.println("Contents of the second chunk after clearing the first:");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Clear second chunk, simulating freeing memory
        secondChunk.clear();
    }
}