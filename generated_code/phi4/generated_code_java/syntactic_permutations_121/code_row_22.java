import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10; // Size of each memory chunk
        byte[] firstChunkData = new byte[size];
        byte[] secondChunkData = new byte[size];

        // Initialize the first chunk with some data
        Arrays.fill(firstChunkData, (byte) 'A');

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunkData, 0, secondChunkData, 0, size);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(secondChunkData));

        // Free allocated memory for the first chunk (in Java, this is handled by garbage collection)
        firstChunkData = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing the first chunk: " + Arrays.toString(secondChunkData));

        // Free allocated memory for the second chunk
        secondChunkData = null;
    }
}