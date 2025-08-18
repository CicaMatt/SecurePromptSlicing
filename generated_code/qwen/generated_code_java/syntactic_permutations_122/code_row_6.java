import java.util.Arrays;

public class MemoryChunkExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks each of size 10
        int[] chunkOne = new int[size];
        int[] chunkTwo = new int[size];
        
        // Initialize first chunk with some values for demonstration
        Arrays.fill(chunkOne, 42);
        
        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(chunkOne, 0, chunkTwo, 0, size);
        
        // Free the first chunk (in Java, this is done by nullifying the reference)
        chunkOne = null;
        
        // Free the second chunk (in Java, this is done by nullifying the reference)
        chunkTwo = null;
        
        // Suggest JVM to perform garbage collection
        System.gc();
    }
}