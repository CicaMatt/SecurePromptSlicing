import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 16; // Size of each chunk in bytes

        // Allocate first chunk
        ByteBuffer firstChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }

        // Allocate second chunk
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Copy contents of the first chunk into the second chunk
        firstChunk.rewind();
        secondChunk.put(firstChunk);

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk after copying:");
        secondChunk.rewind();
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        // In Java, memory is managed by the garbage collector.
        // We don't manually free memory as in C/C++.
        firstChunk = null; // Nullify reference to the first chunk

        // Print contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing the first chunk:");
        secondChunk.rewind();
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        secondChunk = null; // Nullify reference to the second chunk

        // Suggest garbage collection
        System.gc();
    }
}