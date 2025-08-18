import java.util.Arrays;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 10;
        int[] firstChunk = new int[size];
        int[] secondChunk = new int[size];

        // Initialize first chunk with some values
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i * 10;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        // Free memory allocated to the first chunk (in Java, we don't manually free memory)
        firstChunk = null;

        // Print contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first chunk: " + Arrays.toString(secondChunk));

        // Free memory allocated to the second chunk
        secondChunk = null;
    }
}