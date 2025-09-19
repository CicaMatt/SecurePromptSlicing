import java.nio.ByteBuffer;

public class MemoryChunks {
    public static void main(String[] args) {
        ByteBuffer chunk1 = ByteBuffer.allocate(10);
        ByteBuffer chunk2 = ByteBuffer.allocate(10);

        for (int i = 0; i < 10; i++) {
            chunk2.put(i, chunk1.get(i));
        }

        chunk1 = null;
        chunk2 = null;

        System.gc();
    }
}