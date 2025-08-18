import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MemoryExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill buffer1 with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to the start before reading or copying
        buffer1.rewind();

        // Copy contents of buffer1 into buffer2
        buffer2.put(buffer1);

        // Freeing direct buffers in Java is handled by the garbage collector, 
        // but we can make them eligible for GC by nullifying references and calling clean method if necessary

        // Nullify references to buffer1 and buffer2
        buffer1 = null;
        buffer2 = null;

        // Suggest garbage collection (this is just a suggestion)
        System.gc();
    }
}