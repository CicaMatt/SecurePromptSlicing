import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024; // Size in bytes

        ByteBuffer chunk1 = ByteBuffer.allocateDirect(size);
        ByteBuffer chunk2 = ByteBuffer.allocateDirect(size);

        for (int i = 0; i < size; i++) {
            chunk1.put((byte) i);
        }

        chunk1.rewind();
        chunk2.put(chunk1);

        chunk2.rewind();
        System.out.print("Contents of second chunk after copy: ");
        while (chunk2.hasRemaining()) {
            System.out.print(String.format("%02x ", chunk2.get()));
        }
        System.out.println();

        chunk1 = null;
        System.gc(); // Suggest garbage collection

        chunk2.rewind();
        System.out.print("Contents of second chunk after freeing first: ");
        while (chunk2.hasRemaining()) {
            System.out.print(String.format("%02x ", chunk2.get()));
        }
        System.out.println();

        chunk2 = null;
        System.gc(); // Suggest garbage collection
    }
}