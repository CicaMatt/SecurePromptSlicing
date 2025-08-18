import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        // Allocate first chunk of memory with some initial values
        int[] firstChunk = {1, 2, 3, 4, 5};

        // Allocate second chunk of memory with the same length as the first chunk
        int[] secondChunk = new int[firstChunk.length];

        // Copy contents from first chunk to second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println(Arrays.toString(secondChunk));
    }
}