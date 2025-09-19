import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (for demonstration purposes)
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }
        buffer1.flip();

        // Copy contents from the first chunk into the second chunk
        while (buffer1.hasRemaining()) {
            byte b = buffer1.get();
            buffer2.put(b);
        }

        // Free the first chunk (ByteBuffer does not need explicit freeing in Java)
        buffer1.clear();

        // Print the contents of the second chunk to verify copying
        System.out.println("Contents of the second chunk: " + new String(buffer2.array(), 0, buffer2.position()));

        // Free the second chunk (again, ByteBuffer does not need explicit freeing in Java)
        buffer2.clear();
    }
}