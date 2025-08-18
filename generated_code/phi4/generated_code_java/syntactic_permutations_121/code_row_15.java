import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryManagementExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Copy contents from the first chunk to the second chunk
        for (int i = 0; i < firstChunk.capacity(); i++) {
            firstChunk.put((byte) i); // Fill firstChunk with some data
        }
        
        System.arraycopy(firstChunk.array(), 0, secondChunk.array(), 0, Math.min(firstChunk.capacity(), secondChunk.capacity()));

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(secondChunk.array()));

        // Free the memory allocated to the first chunk by reusing it (Java's GC handles this)
        firstChunk.clear();

        // Print contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing firstChunk: " + Arrays.toString(secondChunk.array()));

        // Free the memory allocated to the second chunk by reusing it
        secondChunk.clear();
    }
}