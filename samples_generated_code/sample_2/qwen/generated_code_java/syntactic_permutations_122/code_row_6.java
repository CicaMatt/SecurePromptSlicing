import java.util.Arrays;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        int[] chunkOne = new int[10];
        int[] chunkTwo = new int[10];

        // Initialize chunkOne with some values for demonstration
        Arrays.fill(chunkOne, 5);

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(chunkOne, 0, chunkTwo, 0, chunkOne.length);

        // In Java, there is no explicit way to free memory.
        // Setting references to null helps with garbage collection.
        chunkOne = null;
        chunkTwo = null;

        // Suggesting JVM to perform garbage collection
        System.gc();
    }
}