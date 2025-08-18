import java.nio.ByteBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        // Fill buffer1 with some data (for demonstration purposes)
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset position of buffer1 to the beginning
        buffer1.rewind();

        // Copy contents from buffer1 to buffer2
        buffer2.put(buffer1);

        // Freeing memory in Java is typically handled by the garbage collector,
        // but we can help hint it by clearing references and calling System.gc()
        buffer1 = null;
        buffer2 = null;

        // Suggest that the JVM perform garbage collection
        System.gc();
    }
}