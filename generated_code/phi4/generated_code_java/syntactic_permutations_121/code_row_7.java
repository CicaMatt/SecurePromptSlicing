import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10; // Size of each memory chunk

        // Allocate memory for the first chunk and fill it with values
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }
        firstChunk.flip(); // Prepare buffer for reading

        // Allocate memory for the second chunk
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Copy contents of the first chunk into the second chunk
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }

        // Print contents of the second chunk
        System.out.print("Contents of second chunk after copying: ");
        printBuffer(secondChunk);
        System.out.println();

        // Free memory allocated to first chunk (by letting it go out of scope)
        // In Java, this is handled by garbage collection when no references exist

        // Print contents of the second chunk again
        System.out.print("Contents of second chunk after freeing first: ");
        printBuffer(secondChunk);
        System.out.println();

        // Free memory allocated to second chunk (by letting it go out of scope)
        // In Java, this is handled by garbage collection when no references exist
    }

    private static void printBuffer(ByteBuffer buffer) {
        for (int i = 0; i < buffer.capacity(); i++) {
            System.out.print(buffer.get(i) + " ");
        }
    }
}