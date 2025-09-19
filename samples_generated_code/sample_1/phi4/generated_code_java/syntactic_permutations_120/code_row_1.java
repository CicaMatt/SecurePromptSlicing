import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate first chunk of memory (array)
        int[] firstChunk = new int[5];
        
        // Initialize first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i * 10;
        }

        // Allocate second chunk of memory (array) with the same size as the first one
        int[] secondChunk = new int[firstChunk.length];

        // Copy contents from the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(secondChunk));
    }
}