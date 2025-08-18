import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        // Allocate first chunk of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        
        // Fill the first chunk with some data
        for (byte i = 1; i <= 10; i++) {
            firstChunk.put(i);
        }
        
        // Allocate second chunk of memory
        ByteBuffer secondChunk = ByteBuffer.allocate(10);
        
        // Copy contents from firstChunk to secondChunk
        firstChunk.flip();
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }
        
        // Print the contents of the second chunk
        secondChunk.flip();  // flip before reading
        byte[] array = new byte[secondChunk.remaining()];
        secondChunk.get(array);
        System.out.println("Contents of the second chunk: " + Arrays.toString(array));
    }
}