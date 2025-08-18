import java.util.Arrays;

public class MemoryAllocation {
    public static void main(String[] args) {
        // Allocate two chunks of memory using byte arrays
        byte[] firstChunk = new byte[10];
        byte[] secondChunk = new byte[firstChunk.length];

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Second Chunk after copying: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk (in Java, this is handled by garbage collection)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Second Chunk after freeing first chunk: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the second chunk
        secondChunk = null;
        
        // Suggest garbage collection (Note: this is only a suggestion and not guaranteed)
        System.gc();
    }
}