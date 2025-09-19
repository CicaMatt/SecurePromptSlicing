import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (byte i = 0; i < 10; i++) {
            firstChunk.put(i);
        }
        
        // Reset position to read from the beginning of the buffer
        firstChunk.flip();

        // Copy contents of the first chunk into the second chunk
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }

        // Prepare to print the contents of the second chunk
        secondChunk.flip();
        
        // Print the contents of the second chunk
        System.out.print("Contents of the second chunk: ");
        for (int i = 0; i < secondChunk.limit(); i++) {
            System.out.print(secondChunk.get() + " ");
        }
    }
}