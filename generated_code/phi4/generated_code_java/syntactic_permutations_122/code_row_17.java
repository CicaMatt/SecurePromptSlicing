import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryManagementExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes.
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (e.g., numbers 0-9).
        for (byte i = 0; i < 10; i++) {
            firstChunk.put(i);
        }
        
        // Print the contents of the first chunk
        System.out.println("First chunk before copy: " + Arrays.toString(firstChunk.array()));

        // Copy the contents of the first chunk into the second chunk.
        byte[] tempArray = new byte[10];
        firstChunk.get(tempArray, 0, 10);
        secondChunk.put(tempArray);

        // Print the contents of the second chunk after copy
        System.out.println("Second chunk after copy: " + Arrays.toString(secondChunk.array()));

        // Clear the first chunk by wrapping a new ByteBuffer around it and releasing the old one.
        firstChunk = null;

        // Freeing is implicit in Java when objects are no longer referenced (garbage collected).

        // The second chunk will be freed automatically when it goes out of scope or program ends.
        // Explicitly clearing for demonstration
        secondChunk.clear();
    }
}