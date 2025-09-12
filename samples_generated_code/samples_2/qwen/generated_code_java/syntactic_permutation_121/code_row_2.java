import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 1024; // Size of each chunk in bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        String data = "Hello, World!";
        byte[] bytes = data.getBytes(StandardCharsets.UTF_8);
        buffer1.put(bytes);

        // Copy contents of the first chunk to the second chunk
        buffer1.rewind(); // Reset position to the beginning of buffer1
        buffer2.put(buffer1);

        // Print contents of the second chunk
        buffer2.rewind();
        byte[] bufferArray = new byte[buffer2.remaining()];
        buffer2.get(bufferArray);
        System.out.println("Contents of the second chunk after copy: " + new String(bufferArray, StandardCharsets.UTF_8));

        // Free memory allocated to the first chunk (in Java, this is handled by the garbage collector)
        buffer1 = null;

        // Print contents of the second chunk again
        buffer2.rewind();
        bufferArray = new byte[buffer2.remaining()];
        buffer2.get(bufferArray);
        System.out.println("Contents of the second chunk after freeing first chunk: " + new String(bufferArray, StandardCharsets.UTF_8));

        // Free memory allocated to the second chunk (in Java, this is handled by the garbage collector)
        buffer2 = null;
    }
}