import java.util.Arrays;

public class MemoryManagementExample {
    public static void main(String[] args) {
        int size = 5;
        int[] firstChunk = new int[size];
        int[] secondChunk = new int[size];

        // Initialize the first chunk with some values
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i + 1;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk after copying
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk by setting it to null (simulated in Java)
        firstChunk = null;

        // Print the contents of the second chunk after freeing the first chunk
        System.out.println("Contents of the second chunk after freeing the first chunk: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the second chunk by setting it to null (simulated in Java)
        secondChunk = null;
        
        // Optional: Explicitly request garbage collection for demonstration purposes
        System.gc();
    }
}