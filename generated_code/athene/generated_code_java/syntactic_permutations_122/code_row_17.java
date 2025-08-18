import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        buffer1.rewind();
        buffer2.put(buffer1);

        buffer1 = null;
        buffer2 = null;

        System.gc();
    }
}