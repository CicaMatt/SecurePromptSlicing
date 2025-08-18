import java.util.Arrays;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory of size 10
        int[] firstChunk = new int[10];
        int[] secondChunk = new int[10];

        // Initialize the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i + 1;
        }

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // In Java, there's no explicit free operation. The garbage collector will handle it.
        // We can simulate "freeing" by nullifying references and allowing GC to collect them
        firstChunk = null;
        secondChunk = null;

        // Suggest the JVM to perform garbage collection (not guaranteed to run)
        System.gc();
    }
}