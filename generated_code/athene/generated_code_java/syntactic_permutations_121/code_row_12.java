import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer chunk1 = ByteBuffer.allocateDirect(size);
        ByteBuffer chunk2 = ByteBuffer.allocateDirect(size);

        for (int i = 0; i < size; i++) {
            chunk1.put((byte) i);
        }

        chunk1.rewind();
        chunk2.put(chunk1);

        System.out.println("Second chunk after copy:");
        chunk2.rewind();
        while (chunk2.hasRemaining()) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        chunk1 = null;

        System.gc(); // Suggest garbage collection

        System.out.println("Second chunk before free:");
        chunk2.rewind();
        while (chunk2.hasRemaining()) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        chunk2 = null;

        System.gc(); // Suggest garbage collection
    }
}