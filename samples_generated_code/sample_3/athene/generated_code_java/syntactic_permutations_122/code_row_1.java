import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024; // Size of memory chunks in bytes

        ByteBuffer chunk1 = ByteBuffer.allocate(size);
        ByteBuffer chunk2 = ByteBuffer.allocate(size);

        for (int i = 0; i < size; i++) {
            chunk1.put((byte) i);
        }

        chunk1.rewind();
        chunk2.put(chunk1);

        chunk1 = null;
        chunk2 = null;

        System.gc();
    }
}