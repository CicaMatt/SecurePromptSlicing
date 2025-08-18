import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024; // Size of the chunks in bytes

        ByteBuffer chunk1 = ByteBuffer.allocate(size);
        ByteBuffer chunk2 = ByteBuffer.allocate(size);

        for (int i = 0; i < size; i++) {
            chunk1.put((byte) i);
        }

        chunk1.flip();
        chunk2.put(chunk1);

        System.out.println("Contents of chunk1:");
        printBuffer(chunk1);

        // Freeing the memory allocated to chunk1
        chunk1 = null;

        System.out.println("Contents of chunk2:");
        chunk2.flip();
        printBuffer(chunk2);

        // Freeing the memory allocated to chunk2
        chunk2 = null;
    }

    private static void printBuffer(ByteBuffer buffer) {
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
        System.out.println();
    }
}