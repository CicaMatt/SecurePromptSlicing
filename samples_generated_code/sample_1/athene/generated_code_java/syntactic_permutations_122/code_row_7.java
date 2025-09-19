import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer chunk1 = ByteBuffer.allocate(10);
        ByteBuffer chunk2 = ByteBuffer.allocate(10);

        for (int i = 0; i < 10; i++) {
            chunk1.put((byte) i);
        }

        chunk1.rewind();
        chunk2.put(chunk1);

        chunk1 = null;
        System.gc();

        chunk2 = null;
        System.gc();
    }
}