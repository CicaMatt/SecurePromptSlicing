import java.nio.Buffer;
import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        ByteBuffer destination = ByteBuffer.allocate(source.length);
        
        copyBytes(destination, source, source.length);
        
        // Reset position to read from the beginning
        destination.flip();
        
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
    }

    public static void copyBytes(ByteBuffer dest, byte[] src, int numBytes) {
        if (numBytes > src.length || numBytes < 0) {
            throw new IllegalArgumentException("Invalid number of bytes to copy");
        }
        
        dest.put(src, 0, numBytes);
    }
}