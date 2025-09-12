import java.util.Arrays;

public class MemoryCopyExample {

    public static void main(String[] args) {
        int size = 5;
        
        // Allocate memory for first and second chunks
        int[] firstChunk = new int[size];
        int[] secondChunk = new int[size];
        
        // Initialize the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i * 10;
        }
        
        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);
        
        // Print contents of the second chunk after copying
        System.out.println("Contents of the second chunk after copying: " + Arrays.toString(secondChunk));
        
        // Free the memory allocated to the first chunk (simulated by setting it to null)
        firstChunk = null;
        
        // Print contents of the second chunk after freeing the first chunk's memory
        System.out.println("Contents of the second chunk after freeing the first chunk: " + Arrays.toString(secondChunk));
        
        // Free the memory allocated to the second chunk (simulated by setting it to null)
        secondChunk = null;
    }
}