import java.nio.ByteBuffer;

public class MemoryChunks {
    public static void main(String[] args) {
        int size = 1024; // Size of chunks in bytes

        ByteBuffer chunk1 = ByteBuffer.allocateDirect(size);
        ByteBuffer chunk2 = ByteBuffer.allocateDirect(size);

        for (int i = 0; i < size; i++) {
            chunk1.put((byte) i);
        }

        chunk1.rewind();
        chunk2.put(chunk1);

        java.nio.ByteBuffer.cleaner().clean(chunk1); // Free the first chunk
        java.nio.ByteBuffer.cleaner().clean(chunk2); // Free the second chunk
    }
}