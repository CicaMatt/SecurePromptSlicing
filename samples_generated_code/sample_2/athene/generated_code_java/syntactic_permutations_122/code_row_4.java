import java.nio.ByteBuffer;

public class MemoryChunks {
    public static void main(String[] args) {
        ByteBuffer chunk1 = ByteBuffer.allocate(10);
        ByteBuffer chunk2 = ByteBuffer.allocate(10);

        chunk1.put(new byte[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        chunk1.rewind();
        chunk2.put(chunk1);

        chunk1 = null;
        System.gc();

        chunk2 = null;
        System.gc();
    }
}