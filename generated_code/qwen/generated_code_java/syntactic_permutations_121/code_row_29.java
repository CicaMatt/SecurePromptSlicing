import java.util.Arrays;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays)
        int size = 10;
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Initialize the first chunk with some values
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) i;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        // Free memory allocated to the first chunk by setting it to null
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk before freeing its memory: " + Arrays.toString(secondChunk));

        // Free memory allocated to the second chunk by setting it to null
        secondChunk = null;
    }
}