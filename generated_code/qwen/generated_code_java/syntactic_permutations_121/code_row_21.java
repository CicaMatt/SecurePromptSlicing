import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 10; // Size of each memory chunk

        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        // Fill the first buffer with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) ('A' + i));
        }

        // Copy contents of the first chunk to the second chunk
        buffer1.flip();
        buffer2.put(buffer1);

        // Print contents of the second chunk
        buffer2.flip();
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
        System.out.println();

        // Freeing memory allocated to the first chunk is handled by the garbage collector in Java

        // Reset and print contents of the second chunk again for demonstration
        buffer2.flip();
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
        System.out.println();

        // Freeing memory allocated to the second chunk is handled by the garbage collector in Java
    }
}