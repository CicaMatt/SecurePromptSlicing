import java.util.Arrays;

public class MemoryChunkCopy {

    public static void main(String[] args) {
        int size = 5;
        
        // Allocate and initialize first chunk
        int[] firstChunk = new int[size];
        Arrays.fill(firstChunk, 1);

        // Allocate second chunk
        int[] secondChunk = new int[size];

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying: " + Arrays.toString(secondChunk));

        // Simulate freeing memory allocated to the first chunk (set reference to null)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first chunk: " + Arrays.toString(secondChunk));

        // Simulate freeing memory allocated to the second chunk
        secondChunk = null;
    }
}