import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer source = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            source.put((byte) i);
        }
        ByteBuffer destination = ByteBuffer.allocate(size);
        source.flip();
        destination.put(source);
        destination.flip();
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
    }
}