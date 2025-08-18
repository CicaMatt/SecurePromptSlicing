import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer source = ByteBuffer.allocate(10);
        ByteBuffer destination = ByteBuffer.allocate(10);

        for (int i = 0; i < 10; i++) {
            source.put((byte) i);
        }

        source.rewind();
        destination.put(source);

        System.out.println("Contents of the second chunk after copy:");
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