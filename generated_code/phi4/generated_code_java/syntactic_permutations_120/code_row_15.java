import java.nio.ByteBuffer;

public class MemoryCopyExample {

    public static void main(String[] args) {
        // Allocate first chunk of memory with 10 bytes
        ByteBuffer firstChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (for example, numbers 0 to 9)
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) i);
        }
        
        // Allocate second chunk of memory with same size
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Copy contents from the first chunk into the second chunk
        firstChunk.flip(); // Prepare for reading
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }

        // Print the contents of the second chunk
        secondChunk.flip(); // Prepare for reading
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
    }
}