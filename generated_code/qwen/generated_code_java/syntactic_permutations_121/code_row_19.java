import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 1024;
        
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('A' + i % 26));
        }

        // Reset position to start before copying
        firstChunk.flip();

        // Copy the contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Reset position to start for printing
        secondChunk.flip();
        
        // Print the second chunk
        System.out.println("Second chunk after copy:");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Freeing memory in Java is typically handled by garbage collection,
        // but we can clear and compact buffers to hint at it.
        firstChunk.clear();
        firstChunk = null;

        // Print the second chunk again
        secondChunk.flip();
        System.out.println("Second chunk after freeing first chunk:");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Freeing memory in Java is typically handled by garbage collection,
        // but we can clear and compact buffers to hint at it.
        secondChunk.clear();
        secondChunk = null;
    }
}