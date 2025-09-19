import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10; // Size of each chunk in bytes
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data (example: numbers 0 to 9)
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }
        
        // Reset position of firstChunk for reading
        firstChunk.flip();

        // Copy contents from firstChunk into secondChunk
        secondChunk.clear();
        secondChunk.put(firstChunk);

        // Prepare to read the data from secondChunk
        secondChunk.flip();

        // Print the contents of the second chunk
        byte[] data = new byte[secondChunk.remaining()];
        secondChunk.get(data);
        System.out.println("Contents of the second chunk: " + Arrays.toString(data));
    }
}