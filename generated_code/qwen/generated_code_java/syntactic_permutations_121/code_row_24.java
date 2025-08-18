import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 16; // Size of each memory chunk in bytes
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        String data = "Hello, World!";
        byte[] bytes = data.getBytes(StandardCharsets.UTF_8);
        firstChunk.put(bytes);

        // Reset position to start before copying
        firstChunk.flip();

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Reset position to start for reading
        secondChunk.flip();

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk:");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Clear the first chunk (simulating freeing memory)
        firstChunk.clear();

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after clearing first chunk:");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Clear the second chunk (simulating freeing memory)
        secondChunk.clear();
    }
}