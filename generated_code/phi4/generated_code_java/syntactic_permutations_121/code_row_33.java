import java.nio.ByteBuffer;

public class MemoryCopyExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill first buffer with some data
        for (byte i = 0; i < buffer1.limit(); i++) {
            buffer1.put(i);
        }
        
        // Copy contents from the first chunk to the second chunk
        buffer1.flip();
        buffer2.put(buffer1);

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk after copy:");
        buffer2.flip();
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get() + " ");
        }
        System.out.println();

        // Free allocated to the first chunk by clearing it
        buffer1.clear();

        // Print contents of the second chunk after freeing the first chunk
        System.out.println("Contents of the second chunk after freeing the first chunk:");
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get() + " ");
        }
        System.out.println();

        // Free allocated to the second chunk by clearing it
        buffer2.clear();
    }
}