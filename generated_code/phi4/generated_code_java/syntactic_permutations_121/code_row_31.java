import java.util.Arrays;

public class MemoryCopyExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays in Java)
        int[] firstChunk = new int[10];
        int[] secondChunk = new int[firstChunk.length];

        // Fill the first chunk with some data
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i * 2;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        // Simulate freeing the memory allocated to the first chunk (not applicable in Java as it's garbage collected)
        
        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after 'freeing' first chunk: " + Arrays.toString(secondChunk));

        // Simulate freeing the memory allocated to the second chunk by letting it go out of scope
    }
}