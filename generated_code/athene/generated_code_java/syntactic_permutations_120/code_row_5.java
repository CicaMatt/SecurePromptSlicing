import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        int size = 1024; // Size of chunks in bytes
        ByteBuffer source = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            source.put((byte) i);
        }
        
        ByteBuffer destination = ByteBuffer.allocate(size);
        source.rewind();
        destination.put(source);
        
        destination.rewind();
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
    }
}