import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer source = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            source.put((byte) i);
        }
        
        ByteBuffer destination = ByteBuffer.allocate(size);
        destination.put(source.array());
        
        System.out.println("Contents of the second chunk:");
        destination.rewind();
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
        System.out.println();

        // Freeing memory is not applicable in Java, but we can nullify references
        source = null;
        destination = null;
    }
}