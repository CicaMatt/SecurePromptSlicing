import java.nio.ByteBuffer;

public class MemoryOperationExample {
    public static void main(String[] args) {
        int size = 10; // Size of the memory chunks

        // Allocate memory for the first chunk
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) ('A' + i));
        }

        // Reset position to read from the beginning
        buffer1.rewind();

        // Allocate memory for the second chunk
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Reset position to read from the beginning
        buffer2.rewind();

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy:");
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
        System.out.println();

        // Free memory allocated to the first chunk (not possible in Java, GC will handle it)

        // Reset position to read from the beginning
        buffer2.rewind();

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first chunk:");
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
        System.out.println();

        // Free memory allocated to the second chunk (not possible in Java, GC will handle it)
    }
}