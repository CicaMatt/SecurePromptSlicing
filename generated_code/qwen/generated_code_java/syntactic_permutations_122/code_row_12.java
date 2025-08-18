import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of 10 bytes using ByteBuffer
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill the first chunk with some data (e.g., ASCII values for 'a' to 'j')
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) ('a' + i));
        }

        // Reset the position of buffer1 to the beginning before reading
        buffer1.rewind();

        // Copy the contents of the first chunk into the second chunk
        for (int i = 0; i < 10; i++) {
            buffer2.put(buffer1.get());
        }

        // Freeing memory in Java is handled by the garbage collector, but we can clear references
        buffer1.clear();
        buffer2.clear();

        // Typically, you would not explicitly free memory in Java, 
        // but setting references to null helps with garbage collection
        buffer1 = null;
        buffer2 = null;

        // Suggesting garbage collector to run (though it's just a suggestion)
        System.gc();
    }
}