import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10; // Size of each memory chunk

        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data (e.g., numbers 0 to 9)
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }
        firstChunk.flip(); // Prepare for reading

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Print contents of the second chunk
        System.out.print("Contents of the second chunk after copy: ");
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk (Java's GC handles this)

        // Print contents of the second chunk again
        secondChunk.flip(); // Reset position for reading
        System.out.print("Contents of the second chunk after freeing first: ");
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk (Java's GC handles this)
    }
}