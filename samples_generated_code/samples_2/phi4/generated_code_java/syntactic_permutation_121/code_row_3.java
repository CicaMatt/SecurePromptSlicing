import java.util.Arrays;

public class MemoryManagement {

    public static void main(String[] args) {
        // Allocate two chunks of memory
        int size = 10;
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Fill the first chunk with some data (for example, numbers from 0 to 9)
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) i;
        }

        // Copy contents of the first chunk into the second
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk (in Java, this is handled by garbage collector)
        firstChunk = null;

        // Explicitly request garbage collection for demonstration purposes
        System.gc();

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the second chunk (in Java, this is handled by garbage collector)
        secondChunk = null;

        // Explicitly request garbage collection for demonstration purposes
        System.gc();
    }
}