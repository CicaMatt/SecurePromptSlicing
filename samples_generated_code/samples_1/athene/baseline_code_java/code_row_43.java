import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer source = ByteBuffer.allocate(size);
        ByteBuffer destination = ByteBuffer.allocate(size);

        for (int i = 0; i < size; i++) {
            source.put((byte) i);
        }

        source.rewind();
        destination.put(source);

        destination.flip();
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
    }
}