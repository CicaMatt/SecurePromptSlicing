import java.util.Arrays;

public class MemoryManipulation {
    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays)
        int[] firstChunk = new int[10];
        int[] secondChunk = new int[firstChunk.length];

        // Initialize the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i + 1;
        }

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk (not possible in Java explicitly)
        firstChunk = null;

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after 'freeing' the first chunk: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the second chunk (not possible in Java explicitly)
        secondChunk = null;

        // Since Java handles memory management automatically, we cannot force deallocation.
        // However, setting references to null is a good practice to suggest garbage collection.
    }
}