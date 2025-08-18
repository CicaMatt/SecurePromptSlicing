import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        int size = 5;
        int[] firstChunk = new int[size];
        int[] secondChunk = new int[size];

        // Allocate and initialize the first chunk
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i * 2;
        }

        // Copy contents from the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.println("Second Chunk after copy: " + Arrays.toString(secondChunk));

        // Free memory allocated to the first chunk (implicitly done by Java's garbage collector)

        // Print the contents of the second chunk again
        System.out.println("Second Chunk after freeing first chunk: " + Arrays.toString(secondChunk));

        // Free memory allocated to the second chunk (implicitly done by Java's garbage collector)
    }
}