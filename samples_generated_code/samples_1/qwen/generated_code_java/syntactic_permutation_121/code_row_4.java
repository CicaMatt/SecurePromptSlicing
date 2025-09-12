import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate memory for the first chunk
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('A' + i));
        }
        firstChunk.flip();

        // Allocate memory for the second chunk
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);
        secondChunk.flip();

        // Print contents of the second chunk
        System.out.print("Second chunk after copy: ");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Free memory allocated to the first chunk
        ((sun.nio.ch.DirectBuffer) firstChunk).cleaner().clean();
        firstChunk = null;

        // Print contents of the second chunk again
        secondChunk.rewind();
        System.out.print("Second chunk after freeing first chunk: ");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Free memory allocated to the second chunk
        ((sun.nio.ch.DirectBuffer) secondChunk).cleaner().clean();
        secondChunk = null;
    }
}