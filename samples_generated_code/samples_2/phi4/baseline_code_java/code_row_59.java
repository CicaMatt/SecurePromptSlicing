import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10; // Size of each memory chunk in bytes

        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data (e.g., numbers from 0 to 9)
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Print the contents of the second chunk
        secondChunk.flip(); // Set position to zero for reading
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
    }
}