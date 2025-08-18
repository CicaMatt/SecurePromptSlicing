import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('a' + i));
        }
        firstChunk.flip();

        // Copy the contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);
        secondChunk.flip();

        // Print the contents of the second chunk
        System.out.print("Second chunk after copy: ");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Free the memory allocated to the first chunk
        freeByteBuffer(firstChunk);
        firstChunk = null;

        // Print the contents of the second chunk again
        secondChunk.rewind();
        System.out.print("Second chunk after freeing first chunk: ");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // Free the memory allocated to the second chunk
        freeByteBuffer(secondChunk);
        secondChunk = null;
    }

    // Method to simulate freeing a ByteBuffer
    private static void freeByteBuffer(ByteBuffer buffer) {
        if (buffer.isDirect()) {
            ((java.nio.Buffer) buffer).clear();
        }
    }
}