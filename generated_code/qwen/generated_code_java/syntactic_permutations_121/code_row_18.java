import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 1024; // Size of the memory chunks

        // Allocate two chunks of memory using ByteBuffer
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }

        // Reset position before reading or writing
        firstChunk.rewind();

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Reset position for printing
        secondChunk.rewind();

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk:");
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        // Freeing memory in Java is handled by the garbage collector,
        // but we can clear the buffers to release resources.
        firstChunk.clear();
        secondChunk.clear();

        // Print confirmation of clearing
        System.out.println("Memory allocated to both chunks has been freed.");
    }
}