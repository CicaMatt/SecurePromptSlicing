import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < firstChunk.capacity(); i++) {
            firstChunk.put((byte) (i + 1));
        }
        
        // Copy the contents of the first chunk into the second chunk
        firstChunk.flip();
        secondChunk.put(firstChunk);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk.array()));

        // Free the memory allocated to the first chunk (No explicit free in Java; relying on garbage collection)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first: " + Arrays.toString(secondChunk.array()));

        // Free the memory allocated to the second chunk
        secondChunk = null;

        // Explicitly request garbage collection (No guarantee it will collect immediately)
        System.gc();
    }
}