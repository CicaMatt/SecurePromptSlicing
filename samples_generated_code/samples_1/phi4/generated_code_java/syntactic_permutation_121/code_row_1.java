import java.nio.ByteBuffer;

public class MemoryManagementExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (e.g., numbers 0 to 9)
        for (int i = 0; i < firstChunk.capacity(); i++) {
            firstChunk.put((byte) i);
        }
        
        // Copy the contents of the first chunk into the second chunk
        firstChunk.flip();
        secondChunk.put(firstChunk);

        // Print the contents of the second chunk
        System.out.println("Contents of second chunk after copying:");
        printBuffer(secondChunk);

        // Free the memory allocated to the first chunk (no-op in Java as garbage collector handles it)
        
        // Print the contents of the second chunk again
        System.out.println("Contents of second chunk after freeing first chunk's memory:");
        printBuffer(secondChunk);

        // Free the memory allocated to the second chunk (no-op in Java as garbage collector handles it)

        // Optionally, if we want to explicitly set the buffer to be empty:
        secondChunk.clear();
        
        // Print the contents of the second chunk after freeing its memory
        System.out.println("Contents of second chunk after clearing:");
        printBuffer(secondChunk);
    }

    private static void printBuffer(ByteBuffer buffer) {
        buffer.flip();  // Prepare for reading
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
        System.out.println();
        buffer.clear(); // Reset the buffer for potential reuse
    }
}