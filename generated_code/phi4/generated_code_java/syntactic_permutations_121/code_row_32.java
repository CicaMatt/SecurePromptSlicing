import java.nio.ByteBuffer;

public class MemoryCopyExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10; // Example size

        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) (i + 1));
        }
        
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Copy contents of the first chunk into the second
        firstChunk.flip(); // Prepare to read from buffer
        secondChunk.put(firstChunk);
        
        // Print the contents of the second chunk
        System.out.print("Contents of the second chunk after copy: ");
        printBuffer(secondChunk);
        
        // Free memory allocated to the first chunk (in Java, this is handled by GC)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("\nContents of the second chunk after freeing first chunk: ");
        printBuffer(secondChunk);

        // Free memory of the second chunk (also handled by GC in Java)
        secondChunk = null;
    }

    private static void printBuffer(ByteBuffer buffer) {
        buffer.flip(); // Prepare to read from buffer
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
        buffer.clear();
    }
}