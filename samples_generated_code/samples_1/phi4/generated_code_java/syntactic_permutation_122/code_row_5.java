import java.util.Arrays;

public class MemoryManagement {

    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory each of size 10
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Fill the first chunk with some example data
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) (i + 1);
        }

        System.out.println("First Chunk: " + Arrays.toString(firstChunk));

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        System.out.println("Second Chunk after copying: " + Arrays.toString(secondChunk));

        // Free the first chunk (in Java, this is handled by garbage collection)
        firstChunk = null;

        // Free the second chunk (in Java, this is also handled by garbage collection)
        secondChunk = null;
        
        // Suggest to JVM to run garbage collector
        System.gc();
    }
}