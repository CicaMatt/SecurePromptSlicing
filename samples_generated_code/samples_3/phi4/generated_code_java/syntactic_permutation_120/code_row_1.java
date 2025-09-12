import java.util.Arrays;

public class MemoryAllocator {

    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory
        int[] chunk1 = new int[size];
        int[] chunk2 = new int[size];
        
        // Initialize first chunk with some values
        for (int i = 0; i < size; i++) {
            chunk1[i] = i + 1;
        }
        
        // Copy contents of the first chunk into the second chunk
        System.arraycopy(chunk1, 0, chunk2, 0, size);
        
        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(chunk2));
    }
}