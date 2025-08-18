import java.util.Arrays;

public class MemoryCopyExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays in Java)
        int[] firstChunk = {1, 2, 3, 4, 5};
        int[] secondChunk = new int[firstChunk.length];

        // Copy contents of the first chunk into the second chunk
        for (int i = 0; i < firstChunk.length; i++) {
            secondChunk[i] = firstChunk[i];
        }

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(secondChunk));
    }
}