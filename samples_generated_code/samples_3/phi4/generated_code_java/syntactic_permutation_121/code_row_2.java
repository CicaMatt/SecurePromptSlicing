import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Copy contents into the first chunk
        byte[] data = {1, 2, 3, 4, 5};
        buffer1.put(data);

        // Print the contents of the first chunk
        System.out.println("Contents of the first chunk: " + Arrays.toString(buffer1.array()));

        // Free the memory allocated to the first chunk
        buffer1 = null;

        // Print the contents of the second chunk (still empty)
        System.out.println("Contents of the second chunk: " + Arrays.toString(buffer2.array()));

        // Free the memory allocated to the second chunk
        buffer2 = null;
    }
}