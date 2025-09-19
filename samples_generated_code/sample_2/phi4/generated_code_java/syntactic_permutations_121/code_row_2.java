import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Copy contents from the first chunk to a string for demonstration purposes
        String content = "Hello";
        byte[] bytes = content.getBytes(StandardCharsets.UTF_8);
        
        if (bytes.length > buffer1.capacity()) {
            throw new IllegalArgumentException("Content too large for allocated memory");
        }

        buffer1.put(bytes);

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1.array(), 0, bytes.length);

        // Print the contents of the second chunk
        System.out.println(new String(buffer2.array(), 0, bytes.length));

        // Free memory allocated to the first chunk (in Java, this is handled by garbage collection)
        buffer1 = null;

        // Print the contents of the second chunk again
        System.out.println(new String(buffer2.array(), 0, bytes.length));

        // Free the memory for the second chunk as well
        buffer2 = null;
    }
}