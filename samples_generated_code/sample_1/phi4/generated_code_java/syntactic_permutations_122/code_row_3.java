import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryManagement {

    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10 bytes
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with example data (0 to 9)
        for (byte i = 0; i < 10; i++) {
            firstChunk.put(i);
        }

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk.array(), 0, firstChunk.remaining());

        // Print the contents of the second chunk
        System.out.println("Contents of second chunk: " + Arrays.toString(secondChunk.array()));

        // Free the first chunk by releasing its underlying array if possible
        byte[] releasedArray = releaseMemory(firstChunk);
        if (releasedArray != null) {
            System.out.println("First chunk memory freed.");
        }

        // Since Java's garbage collector will handle the second chunk,
        // explicitly "free" it by making it unreachable
        secondChunk = null;
        
        // Suggest garbage collection (not guaranteed to run immediately)
        System.gc();
        System.out.println("Second chunk suggested for garbage collection.");
    }

    private static byte[] releaseMemory(ByteBuffer buffer) {
        if (!buffer.isDirect()) {
            return buffer.array();  // Return the backing array of non-direct buffers
        }
        return null;  // Direct buffers don't have a method to get their backing array in Java
    }
}