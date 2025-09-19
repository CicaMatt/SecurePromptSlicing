import java.nio.ByteBuffer;

public class MemoryCopyExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory, each 10 bytes long
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) ('A' + i));
        }
        firstChunk.flip(); // Prepare for reading

        // Copy contents of first chunk into second chunk
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }

        // Print the contents of the second chunk
        System.out.print("Contents of second chunk after copy: ");
        secondChunk.rewind();
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get() + " ");
        }
        System.out.println();

        // Free memory allocated to first chunk (automatically handled by Java's garbage collector)

        // Print the contents of the second chunk again
        System.out.print("Contents of second chunk after freeing first: ");
        secondChunk.rewind();
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get() + " ");
        }
        System.out.println();

        // Free memory allocated to second chunk (automatically handled by Java's garbage collector)
    }
}