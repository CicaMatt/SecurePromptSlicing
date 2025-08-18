import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each 10 bytes long
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with example data (numbers 0 to 9)
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }
        
        // Copy contents from the first chunk into the second
        buffer2.clear();
        buffer2.put(buffer1);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(buffer2.array()));
    }
}