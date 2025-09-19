import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 1024; // Size of each memory chunk in bytes

        // Allocate first chunk of memory
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Allocate second chunk of memory
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        // Copy the contents of the first chunk into the second chunk
        buffer1.rewind();
        buffer2.put(buffer1);

        // Print the contents of the second chunk
        buffer2.rewind();
        System.out.print("Contents of the second chunk after copy: ");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the first chunk (not possible in Java, GC handles it)

        // Print the contents of the second chunk again
        buffer2.rewind();
        System.out.print("Contents of the second chunk after freeing first chunk: ");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk (not possible in Java, GC handles it)
    }
}