import java.nio.ByteBuffer;

public class MemoryOperationExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate memory for the first chunk
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }
        firstChunk.flip();
        
        // Allocate memory for the second chunk
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);
        secondChunk.flip();

        // Print contents of the second chunk
        System.out.println("Second chunk after copying:");
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the first chunk
        firstChunk = null;
        System.gc();

        // Print contents of the second chunk again
        secondChunk.rewind();
        System.out.println("Second chunk after freeing first chunk:");
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk
        secondChunk = null;
        System.gc();
    }
}