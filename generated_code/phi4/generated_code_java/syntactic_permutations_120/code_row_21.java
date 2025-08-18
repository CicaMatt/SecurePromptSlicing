import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        // Allocate the first chunk of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(10);

        // Fill the first chunk with some example data (e.g., 0-9)
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }
        
        // Allocate the second chunk of memory
        ByteBuffer buffer2 = ByteBuffer.allocate(buffer1.capacity());

        // Copy contents from the first chunk to the second chunk
        buffer2.put(buffer1);

        // Reset position for reading
        buffer2.flip();

        // Print the contents of the second chunk
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
    }
}