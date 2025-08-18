import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        int size = 10; // Size of each memory chunk

        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data (e.g., numbers from 0 to 9)
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }
        firstChunk.flip(); // Prepare for reading

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(secondChunk.array()));
    }
}