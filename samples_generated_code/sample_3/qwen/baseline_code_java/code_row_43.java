import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate first chunk of memory (array)
        int[] firstChunk = {1, 2, 3, 4, 5};

        // Allocate second chunk of memory (array) with the same length as the first
        int[] secondChunk = new int[firstChunk.length];

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println(Arrays.toString(secondChunk));
    }
}