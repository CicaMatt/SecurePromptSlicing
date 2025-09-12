import java.nio.ByteBuffer;
import java.nio.CharBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 1024; // Size in bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Fill the first chunk with some data (e.g., characters)
        String sampleData = "Hello, World!";
        CharBuffer charBuffer = CharBuffer.wrap(sampleData);
        for (char c : charBuffer.array()) {
            buffer1.putChar(c);
        }
        buffer1.rewind(); // Rewind to start position

        // Copy contents of the first chunk into the second chunk
        while (buffer1.hasRemaining()) {
            buffer2.put(buffer1.get());
        }
        buffer2.rewind(); // Rewind to start position for reading

        // Print the contents of the second chunk
        charBuffer = buffer2.asCharBuffer();
        System.out.println("Contents of second chunk: " + charBuffer.toString());

        // Free memory allocated to the first chunk (not explicitly possible in Java, GC will handle)
        buffer1.clear();

        // Print the contents of the second chunk again to show it is still intact
        charBuffer.rewind(); // Rewind to start position for reading
        System.out.println("Contents of second chunk after freeing first: " + charBuffer.toString());

        // Free memory allocated to the second chunk (not explicitly possible in Java, GC will handle)
        buffer2.clear();
    }
}