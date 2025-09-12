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
        for (int i = 0; i < buffer.capacity(); i++) {
            System.out.print(buffer.get(i) + " ");
        }
        System.out.println();
    }
}