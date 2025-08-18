import java.util.Arrays;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of each size 10
        int[] chunkOne = new int[10];
        int[] chunkTwo = new int[10];

        // Initialize chunkOne with some values (for demonstration)
        for (int i = 0; i < chunkOne.length; i++) {
            chunkOne[i] = i + 1;
        }

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(chunkOne, 0, chunkTwo, 0, chunkOne.length);

        // "Free" the first chunk by setting it to null (Java's garbage collector will handle it)
        chunkOne = null;

        // "Free" the second chunk by setting it to null (Java's garbage collector will handle it)
        chunkTwo = null;

        // Suggest to the JVM that it can run the garbage collector
        System.gc();
    }
}