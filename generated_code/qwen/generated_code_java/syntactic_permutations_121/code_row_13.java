import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('A' + i));
        }

        // Reset position to read from the beginning
        firstChunk.rewind();

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Reset position to read from the beginning
        secondChunk.rewind();

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying:");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // "Free" the memory allocated to the first chunk by nullifying it
        firstChunk = null;

        // Print the contents of the second chunk again
        secondChunk.rewind();
        System.out.println("Contents of the second chunk after freeing the first chunk:");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // "Free" the memory allocated to the second chunk by nullifying it
        secondChunk = null;
    }
}