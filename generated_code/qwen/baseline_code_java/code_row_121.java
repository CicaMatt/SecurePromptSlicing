import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10; // Size of each buffer
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('a' + i));
        }

        // Reset position to start of buffer before reading or writing
        firstChunk.rewind();

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Reset position to start of buffer before reading
        secondChunk.rewind();

        // Print contents of the second chunk
        System.out.print("Contents of second chunk after copy: ");
        for (int i = 0; i < size; i++) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Free memory allocated to the first chunk by clearing it
        firstChunk.clear();

        // Print contents of the second chunk again to show it's unaffected
        secondChunk.rewind();
        System.out.print("Contents of second chunk after freeing first chunk: ");
        for (int i = 0; i < size; i++) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Free memory allocated to the second chunk by clearing it
        secondChunk.clear();
    }
}