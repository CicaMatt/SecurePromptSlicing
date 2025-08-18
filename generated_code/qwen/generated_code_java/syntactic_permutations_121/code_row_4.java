import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryAllocation {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start before copying
        buffer1.rewind();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Reset position to start for printing
        buffer2.rewind();
        
        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying: " + Arrays.toString(buffer2.array()));

        // Clear the first buffer (conceptually freeing memory)
        buffer1.clear();

        // Reset position to start for printing again
        buffer2.rewind();
        
        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after clearing first: " + Arrays.toString(buffer2.array()));

        // Clear the second buffer (conceptually freeing memory)
        buffer2.clear();
    }
}