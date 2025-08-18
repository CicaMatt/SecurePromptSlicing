import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        ByteBuffer source = ByteBuffer.allocate(1024);
        for (int i = 0; i < 1024; i++) {
            source.put((byte) i);
        }
        
        ByteBuffer destination = ByteBuffer.allocate(1024);
        source.rewind();
        destination.put(source);
        
        destination.rewind();
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
    }
}