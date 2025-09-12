import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        byte[] firstChunk = new byte[10];
        byte[] secondChunk = new byte[firstChunk.length];

        // Initialize the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = (byte) ('A' + i);
        }

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        // In Java, memory is managed by the garbage collector, so we don't explicitly free memory.
        // However, to simulate freeing the first chunk, we can set it to null and suggest garbage collection.
        firstChunk = null;
        System.gc();

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after 'freeing' the first chunk: " + Arrays.toString(secondChunk));
    }
}