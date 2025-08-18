import java.nio.ByteBuffer;

public class MemoryChunks {
    public static void main(String[] args) {
        ByteBuffer chunk1 = ByteBuffer.allocate(1024);
        ByteBuffer chunk2 = ByteBuffer.allocate(1024);

        for (int i = 0; i < 1024; i++) {
            chunk1.put((byte) i);
        }

        chunk1.rewind();
        chunk2.put(chunk1);

        System.out.println("Contents of chunk2 after copy:");
        printBuffer(chunk2);

        chunk1 = null;
        System.gc();

        chunk2.rewind();
        System.out.println("Contents of chunk2 after freeing chunk1:");
        printBuffer(chunk2);

        chunk2 = null;
        System.gc();
    }

    private static void printBuffer(ByteBuffer buffer) {
        buffer.rewind();
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
        System.out.println();
    }
}