import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(8);
        ByteBuffer buffer2 = ByteBuffer.allocate(8);

        // Initialize the first chunk with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) (i + 65)); // ASCII values of 'A' to 'H'
        }

        // Reset position to start copying from the beginning
        buffer1.rewind();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy:");
        buffer2.flip(); // Prepare buffer for reading
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk by setting it to null and calling garbage collector
        buffer1 = null;
        System.gc();

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first chunk:");
        buffer2.flip(); // Prepare buffer for reading
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk by setting it to null and calling garbage collector
        buffer2 = null;
        System.gc();
    }
}