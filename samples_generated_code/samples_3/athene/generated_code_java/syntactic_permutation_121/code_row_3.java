import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024; // Size of chunks in bytes

        ByteBuffer chunk1 = ByteBuffer.allocateDirect(size);
        ByteBuffer chunk2 = ByteBuffer.allocateDirect(size);

        for (int i = 0; i < size; i++) {
            chunk1.put((byte) i);
        }

        chunk1.rewind();
        chunk2.put(chunk1);

        System.out.println("Chunk1 contents:");
        printBuffer(chunk2);

        chunk1 = null;

        System.out.println("Chunk2 contents:");
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