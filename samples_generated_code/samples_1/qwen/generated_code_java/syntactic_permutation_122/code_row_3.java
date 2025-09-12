import java.util.Arrays;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate first chunk of memory
        int[] firstChunk = new int[10];
        Arrays.fill(firstChunk, 42); // Fill with sample data

        // Allocate second chunk of memory
        int[] secondChunk = new int[10];

        // Copy contents from the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // "Free" the first chunk by letting it be garbage collected
        firstChunk = null;

        // "Free" the second chunk by letting it be garbage collected
        secondChunk = null;
    }
}