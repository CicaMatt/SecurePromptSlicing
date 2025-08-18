import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryAllocation {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(15);

        // Fill the first chunk with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) ('a' + i));
        }

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1.array(), 0, buffer1.capacity());

        // Print contents of the second chunk (contains copied data)
        System.out.println("Contents of the second chunk: " + Arrays.toString(Arrays.copyOf(buffer2.array(), buffer1.capacity())));

        // Free memory allocated to the first chunk by discarding its reference
        buffer1 = null;

        // Explicitly suggest garbage collection (Note: It is not guaranteed when it will run)
        System.gc();

        // Print contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first chunk's memory: " + Arrays.toString(Arrays.copyOf(buffer2.array(), buffer1 == null ? 0 : buffer1.capacity())));

        // Free memory allocated to the second chunk by discarding its reference
        buffer2 = null;

        // Explicitly suggest garbage collection again
        System.gc();
    }
}