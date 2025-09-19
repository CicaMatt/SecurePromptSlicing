import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }

        buffer1.rewind();
        buffer2.put(buffer1);

        // Freeing the first chunk
        buffer1 = null;

        // Freeing the second chunk
        buffer2 = null;

        System.gc();
    }
}