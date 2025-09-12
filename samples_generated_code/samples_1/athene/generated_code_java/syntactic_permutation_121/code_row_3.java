import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer chunk1 = ByteBuffer.allocate(size);
        ByteBuffer chunk2 = ByteBuffer.allocate(size);

        for (int i = 0; i < size; i++) {
            chunk1.put((byte) i);
        }

        chunk1.flip();
        chunk2.put(chunk1);

        System.out.println("Contents of second chunk after copy:");
        chunk2.rewind();
        while (chunk2.hasRemaining()) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        chunk1 = null;
        System.gc();

        System.out.println("Contents of second chunk after freeing first chunk:");
        chunk2.rewind();
        while (chunk2.hasRemaining()) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        chunk2 = null;
        System.gc();
    }
}