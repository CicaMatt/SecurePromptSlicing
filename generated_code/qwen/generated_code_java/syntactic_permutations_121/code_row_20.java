import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 16; // Size of each memory chunk

        // Allocate first chunk of memory
        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }
        firstChunk.rewind();

        // Allocate second chunk of memory
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        // Copy contents from first chunk to second chunk
        firstChunk.rewind();
        secondChunk.put(firstChunk);

        // Print contents of the second chunk
        secondChunk.rewind();
        System.out.print("Contents of second chunk after copy: ");
        for (int i = 0; i < size; i++) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the first chunk (not explicitly needed in Java, but clearing)
        firstChunk.clear();
        firstChunk = null;

        // Print contents of the second chunk again
        secondChunk.rewind();
        System.out.print("Contents of second chunk after freeing first chunk: ");
        for (int i = 0; i < size; i++) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk (not explicitly needed in Java, but clearing)
        secondChunk.clear();
        secondChunk = null;
    }
}