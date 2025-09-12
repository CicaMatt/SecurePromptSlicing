import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        int size = 1024; // Size of the chunks in bytes

        // Allocate first chunk of memory
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }

        // Allocate second chunk of memory
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Copy from first chunk to second chunk
        firstChunk.rewind(); // Reset position to the start
        secondChunk.put(firstChunk);

        // Print the second chunk
        System.out.println("Second chunk after copy:");
        secondChunk.rewind(); // Reset position to the start
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the first chunk
        firstChunk = null;

        // Print the second chunk again
        System.out.println("Second chunk after freeing first chunk:");
        secondChunk.rewind(); // Reset position to the start
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk
        secondChunk = null;
    }
}