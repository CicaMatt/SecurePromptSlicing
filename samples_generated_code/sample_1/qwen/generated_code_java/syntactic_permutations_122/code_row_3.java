import java.nio.ByteBuffer;

public class MemoryExample {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        buffer1.rewind();
        buffer2.put(buffer1);

        buffer1.clear(); // Freeing the first chunk by clearing it
        buffer2.clear(); // Freeing the second chunk by clearing it
    }
}