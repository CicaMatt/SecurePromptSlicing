import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer source = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            source.put((byte) i);
        }

        ByteBuffer destination = ByteBuffer.allocate(size);
        source.rewind();
        destination.put(source);

        System.out.println("Contents of the second chunk after copy:");
        destination.rewind();
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
        System.out.println();

        // Simulate freeing memory by clearing and nulling
        source.clear();
        source = null;

        System.out.println("Contents of the second chunk after freeing first chunk:");
        destination.rewind();
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
        System.out.println();

        // Simulate freeing memory by clearing and nulling
        destination.clear();
        destination = null;
    }
}