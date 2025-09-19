import java.util.Arrays;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 10;
        int[] firstChunk = new int[size];
        int[] secondChunk = new int[size];

        // Initialize the first chunk with some values
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i + 1;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk (in Java, this is done by allowing garbage collection)
        firstChunk = null;

        // Suggest garbage collection (not guaranteed to run immediately)
        System.gc();

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after first chunk is freed: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the second chunk
        secondChunk = null;

        // Suggest garbage collection (not guaranteed to run immediately)
        System.gc();
    }
}