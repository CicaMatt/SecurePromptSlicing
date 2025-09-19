import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Populate the first buffer with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start copying from the beginning
        buffer1.rewind();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Reset position to start reading from the beginning
        buffer2.rewind();

        // Print the contents of the second chunk
        System.out.print("Contents of the second chunk after copy: ");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the first chunk by nullifying it
        buffer1 = null;

        // Reset position to start reading from the beginning again
        buffer2.rewind();

        // Print the contents of the second chunk
        System.out.print("Contents of the second chunk after freeing the first chunk: ");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk by nullifying it
        buffer2 = null;

        // Suggest garbage collection, though not guaranteed to run immediately
        System.gc();
    }
}