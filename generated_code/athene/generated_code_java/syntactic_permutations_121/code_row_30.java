import java.nio.ByteBuffer;

public class MemoryChunks {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer chunk1 = ByteBuffer.allocate(size);
        ByteBuffer chunk2 = ByteBuffer.allocate(size);

        for (int i = 0; i < size; i++) {
            chunk1.put((byte) i);
        }

        chunk2.put(chunk1.array());

        System.out.println("Contents of chunk1:");
        printBuffer(chunk1);

        chunk1 = null;

        System.out.println("Contents of chunk2:");
        printBuffer(chunk2);

        chunk2 = null;
    }

    private static void printBuffer(ByteBuffer buffer) {
        buffer.rewind();
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
        System.out.println();
    }
}