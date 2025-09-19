import java.nio.ByteBuffer;

public class MemoryManager {

    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Copy contents from the first chunk to the second chunk
        buffer2.put(buffer1.array());

        // Free the first chunk (in Java, this is done by letting it go out of scope)
        buffer1 = null;

        // Explicitly request garbage collection
        System.gc();

        // Free the second chunk (same as above)
        buffer2 = null;

        // Explicitly request garbage collection again
        System.gc();
    }
}