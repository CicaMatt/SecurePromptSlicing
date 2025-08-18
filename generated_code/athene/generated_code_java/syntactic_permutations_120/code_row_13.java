import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        int chunkSize = 1024;
        ByteBuffer chunk1 = ByteBuffer.allocate(chunkSize);
        ByteBuffer chunk2 = ByteBuffer.allocate(chunkSize);

        for (int i = 0; i < chunkSize; i++) {
            chunk1.put((byte) i);
        }

        chunk1.rewind();
        chunk2.put(chunk1);

        chunk2.rewind();
        while (chunk2.hasRemaining()) {
            System.out.print(chunk2.get() + " ");
        }
    }
}