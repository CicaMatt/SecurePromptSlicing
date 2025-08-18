import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first buffer with some data (for example, numbers 0 to 9)
        for (byte i = 0; i < 10; i++) {
            buffer1.put(i);
        }

        // Copy contents from buffer1 to buffer2
        buffer2.put(buffer1.array(), 0, buffer1.limit());

        // Print the content of both buffers to verify copying
        System.out.println("Buffer 1: " + new String(buffer1.array()));
        System.out.println("Buffer 2: " + new String(buffer2.array()));

        // Explicitly free the memory by clearing and compacting the buffers (not required in Java as GC handles it)
        buffer1.clear();
        buffer1.compact();

        buffer2.clear();
        buffer2.compact();
    }
}