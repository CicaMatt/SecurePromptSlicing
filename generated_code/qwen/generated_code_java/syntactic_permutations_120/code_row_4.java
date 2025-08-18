import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        ByteBuffer source = ByteBuffer.allocate(size);
        ByteBuffer destination = ByteBuffer.allocate(size);

        // Fill the source buffer with some data
        for (int i = 0; i < size; i++) {
            source.put((byte) i);
        }

        // Reset position to start reading from the beginning
        source.rewind();

        // Copy contents of source to destination
        destination.put(source);

        // Reset position to start reading from the beginning
        destination.rewind();

        // Print contents of the destination buffer
        for (int i = 0; i < size; i++) {
            System.out.print(destination.get() + " ");
        }
    }
}