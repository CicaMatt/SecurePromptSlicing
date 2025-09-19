import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate memory for the first chunk (100 bytes)
        ByteBuffer firstChunk = ByteBuffer.allocate(100);
        
        // Initialize the first chunk with some data
        for (int i = 0; i < 50; i++) {
            firstChunk.put((byte) (i + 1)); // Fill the buffer with values from 1 to 50
        }
        firstChunk.flip(); // Reset position to read from the beginning

        // Allocate memory for the second chunk (100 bytes)
        ByteBuffer secondChunk = ByteBuffer.allocate(100);

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying:");
        printBuffer(secondChunk);
        
        // Free memory allocated to the first chunk (handled by garbage collector in Java)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing the first chunk's memory:");
        printBuffer(secondChunk);

        // Free memory allocated to the second chunk (handled by garbage collector in Java)
        secondChunk = null;
    }

    private static void printBuffer(ByteBuffer buffer) {
        byte[] byteArray = new byte[buffer.remaining()];
        buffer.get(byteArray);
        System.out.println(Arrays.toString(byteArray));
    }
}