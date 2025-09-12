import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int chunkSize = 1024;
        ByteBuffer source = ByteBuffer.allocate(chunkSize);
        ByteBuffer destination = ByteBuffer.allocate(chunkSize);

        for (int i = 0; i < chunkSize; i++) {
            source.put((byte) i);
        }

        source.rewind();
        destination.put(source);

        System.out.println("Contents of the second chunk after copy:");
        destination.rewind();
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
        System.out.println();

        source = null;

        System.out.println("Contents of the second chunk after freeing first chunk:");
        destination.rewind();
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
        System.out.println();

        destination = null;
        System.gc();
    }
}