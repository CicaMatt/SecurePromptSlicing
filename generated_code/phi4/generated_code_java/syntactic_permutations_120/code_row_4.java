import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate the first chunk of memory with size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        
        // Fill buffer1 with some sample data (e.g., ASCII values for "Hello")
        String message = "Hello";
        for (int i = 0; i < message.length(); i++) {
            buffer1.put((byte) message.charAt(i));
        }
        buffer1.flip(); // Flip the buffer to prepare it for reading

        // Allocate the second chunk of memory with the same size
        ByteBuffer buffer2 = ByteBuffer.allocate(10);
        
        // Copy contents from buffer1 to buffer2
        buffer2.put(buffer1);

        // Reset position to read from the beginning of buffer2
        buffer2.flip();

        // Print the contents of the second chunk
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
    }
}