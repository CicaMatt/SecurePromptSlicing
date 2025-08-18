import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        int size = 1024; // Size in bytes
        
        ByteBuffer source = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            source.put((byte) i);
        }

        ByteBuffer destination = ByteBuffer.allocate(size);
        
        source.rewind();
        destination.put(source);
        
        System.out.println("Copy completed.");
    }
}