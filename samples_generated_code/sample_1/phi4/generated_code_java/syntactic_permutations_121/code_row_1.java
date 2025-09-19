import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopyExample {

    public static void main(String[] args) {
        int size = 10; // Size of each memory chunk

        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with data (for example, numbers 0 to 9)
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }

        // Copy the contents of the first chunk into the second chunk
        firstChunk.flip(); // Prepare buffer for reading
        secondChunk.clear();
        secondChunk.put(firstChunk);

        // Print the contents of the second chunk
        System.out.println("Second chunk after copy: " + Arrays.toString(secondChunk.array()));

        // Free the memory allocated to the first chunk (implicit in Java, shown here for clarity)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Second chunk after freeing first chunk: " + Arrays.toString(secondChunk.array()));

        // Free the memory allocated to the second chunk (explicitly clear and nullify)
        secondChunk.clear();
        secondChunk = null;
    }
}