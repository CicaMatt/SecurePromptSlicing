import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10.
        int[] firstChunk = new int[10];
        int[] secondChunk = new int[10];

        // Initialize the first chunk with some values for demonstration.
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i + 1;
        }

        System.out.println("First Chunk before copy: " + Arrays.toString(firstChunk));

        // Copy contents of the first chunk into the second chunk.
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        System.out.println("Second Chunk after copy: " + Arrays.toString(secondChunk));

        // In Java, memory management is handled by garbage collector, so there's no explicit 'free'.
        // However, if we want to make the first chunk eligible for garbage collection,
        // we can dereference it by setting it to null.
        
        firstChunk = null;
        
        // Now the firstChunk is eligible for garbage collection.

        System.out.println("First Chunk after nulling: " + (firstChunk == null ? "null" : Arrays.toString(firstChunk)));
    }
}