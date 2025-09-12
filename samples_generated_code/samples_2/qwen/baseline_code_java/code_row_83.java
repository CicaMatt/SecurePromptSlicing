import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10; // Size of each buffer
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Put some data into the first chunk
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('A' + i));
        }

        // Reset position to start before copying
        firstChunk.rewind();

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Reset position to start for printing
        secondChunk.rewind();

        // Print contents of the second chunk
        System.out.print("Contents of the second chunk after copy: ");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get() + " ");
        }
        System.out.println();

        // In Java, we don't explicitly free memory. The garbage collector will handle it.
        // However, to simulate freeing the first chunk, we can just nullify the reference
        firstChunk = null;

        // Print contents of the second chunk again
        secondChunk.rewind();
        System.out.print("Contents of the second chunk after 'freeing' the first chunk: ");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get() + " ");
        }
        System.out.println();

        // Nullify the reference to the second chunk
        secondChunk = null;

        // Suggest garbage collection, though it's not guaranteed to run immediately
        System.gc();
    }
}