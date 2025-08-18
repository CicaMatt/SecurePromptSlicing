import java.nio.ByteBuffer;

public class MemoryExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Initialize buffer1 with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) ('a' + i));
        }

        // Reset the position of buffer1 to start reading from the beginning
        buffer1.rewind();

        // Copy contents of buffer1 into buffer2
        buffer2.put(buffer1);

        // Free the first chunk (Note: In Java, there's no explicit free method. 
        // The garbage collector will handle it when buffer1 goes out of scope)
    }
}