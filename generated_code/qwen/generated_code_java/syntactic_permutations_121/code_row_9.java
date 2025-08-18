import java.util.Arrays;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays)
        int[] firstChunk = new int[5];
        int[] secondChunk = new int[firstChunk.length];

        // Initialize the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i + 1;
        }

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        // In Java, memory is managed by the garbage collector, so we don't explicitly free memory.
        // However, we can help the GC by dereferencing objects that are no longer needed.
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first chunk: " + Arrays.toString(secondChunk));

        // Dereference the second chunk
        secondChunk = null;
    }
}