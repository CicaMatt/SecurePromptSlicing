import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill buffer1 with some example data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start of buffer1 before reading
        buffer1.rewind();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Free the second chunk by dereferencing it
        buffer2 = null;

        // Normally, in Java, you don't explicitly free memory as the garbage collector handles it
        System.gc(); // Suggestion to JVM to perform garbage collection
    }
}