import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer chunk1 = ByteBuffer.allocate(1024);
        ByteBuffer chunk2 = ByteBuffer.allocate(1024);

        for (int i = 0; i < 1024; i++) {
            chunk1.put((byte) i);
        }

        chunk1.flip();
        chunk2.put(chunk1);

        System.out.println("Contents of chunk2 after copy:");
        chunk2.rewind();
        while (chunk2.hasRemaining()) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        chunk1 = null;
        System.gc();

        System.out.println("Contents of chunk2 after freeing chunk1:");
        chunk2.rewind();
        while (chunk2.hasRemaining()) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        chunk2 = null;
        System.gc();
    }
}