import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Initialize the first chunk with some values
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start reading from the beginning
        buffer1.rewind();

        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Freeing memory in Java is typically handled by the garbage collector,
        // but we can help it by nullifying references and calling gc()
        buffer1 = null;
        buffer2 = null;

        // Suggest to JVM that it can run garbage collection
        System.gc();
    }
}