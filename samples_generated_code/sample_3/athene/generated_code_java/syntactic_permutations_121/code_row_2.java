import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer source = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            source.put((byte) i);
        }
        ByteBuffer destination = ByteBuffer.allocate(size);
        destination.put(source.array());
        System.out.println("Contents of the second chunk after copying:");
        printBuffer(destination);

        source = null;
        System.gc();

        System.out.println("Contents of the second chunk after freeing first chunk:");
        printBuffer(destination);

        destination = null;
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