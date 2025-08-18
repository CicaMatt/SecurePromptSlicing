import java.util.Arrays;

public class MemoryCopy {

    public static void main(String[] args) {
        // Allocate two chunks of memory
        int size = 10;
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Initialize the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) (i + 1);
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print both chunks to verify the copy operation
        System.out.println("First Chunk: " + Arrays.toString(firstChunk));
        System.out.println("Second Chunk: " + Arrays.toString(secondChunk));
    }
}