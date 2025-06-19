import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        // Create two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Write some data into the first chunk
        for (int i=0; i<5; i++) {
            buffer1.put((byte)i);
        }

        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1);
    }
}