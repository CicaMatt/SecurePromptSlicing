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
        
        // Reset position to start before copying
        firstChunk.rewind();
        
        // Copy the contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Reset position to start for reading
        secondChunk.rewind();

        // Print the contents of the second chunk
        System.out.print("Contents of the second chunk after copy: ");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Free allocated memory to the first chunk
        // Note: In Java, we don't explicitly free memory. 
        // The garbage collector will handle it when necessary.
        firstChunk = null;

        // Reset position to start for reading again
        secondChunk.rewind();

        // Print the contents of the second chunk
        System.out.print("Contents of the second chunk after freeing the first chunk: ");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Free allocated memory to the second chunk
        secondChunk = null;
    }
}