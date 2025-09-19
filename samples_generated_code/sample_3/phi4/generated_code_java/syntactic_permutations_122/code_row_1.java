import java.nio.ByteBuffer;

public class MemoryCopyExample {

    public static void main(String[] args) {
        // Allocate the first chunk of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(1024);

        // Fill the first chunk with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }
        
        // Allocate the second chunk of memory
        ByteBuffer buffer2 = ByteBuffer.allocate(buffer1.capacity());

        // Copy contents from the first chunk to the second chunk
        buffer2.put(buffer1.array(), 0, buffer1.limit());
        
        // Free the first chunk (in Java, this is handled by garbage collection)
        buffer1 = null;

        // Free the second chunk (also managed by garbage collector)
        buffer2 = null;
        
        // Suggesting JVM to perform garbage collection (though it's not guaranteed)
        System.gc();
    }
}