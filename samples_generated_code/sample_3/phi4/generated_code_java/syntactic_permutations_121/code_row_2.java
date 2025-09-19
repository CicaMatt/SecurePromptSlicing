import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) ('A' + i));
        }
        buffer1.flip();

        // Copy contents from the first chunk to the second chunk
        buffer2.put(buffer1);

        // Print the contents of the second chunk
        System.out.println("Contents of buffer2 after copy:");
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk by compacting the buffer (not truly freeing, but moving data)
        buffer1.clear();
        
        // Print the contents of the second chunk again
        System.out.println("Contents of buffer2 after freeing buffer1:");
        buffer2.flip();  // Rewind to read from beginning
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get() + " ");
        }
    }
}