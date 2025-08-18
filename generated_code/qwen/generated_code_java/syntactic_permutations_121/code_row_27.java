import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 1024; // Size of each chunk

        // Allocate first chunk of memory
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) (i % 256));
        }

        // Allocate second chunk of memory
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        // Copy contents from the first chunk to the second chunk
        buffer1.rewind();
        buffer2.put(buffer1);

        // Print contents of the second chunk
        buffer2.rewind();
        System.out.println("Contents of the second chunk:");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk
        buffer1.clear();
        System.gc(); // Suggesting JVM to garbage collect, but no guarantee

        // Print contents of the second chunk again after freeing the first chunk
        buffer2.rewind();
        System.out.println("Contents of the second chunk after freeing the first:");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk
        buffer2.clear();
        System.gc(); // Suggesting JVM to garbage collect, but no guarantee
    }
}