import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory
        int[] firstChunk = new int[size];
        int[] secondChunk = new int[size];
        
        // Initialize the first chunk with some values
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i * 10;
        }
        
        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);
        
        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(secondChunk));
    }
}