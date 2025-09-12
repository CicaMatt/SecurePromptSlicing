import java.nio.Buffer;
import java.nio.ByteBuffer;

public class ByteCopier {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        ByteBuffer destination = ByteBuffer.allocate(source.length);
        int numberOfBytesToCopy = 3;
        
        copyBytes(destination, source, numberOfBytesToCopy);
        
        // Reset buffer position to read copied bytes
        destination.flip();
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
    }

    public static void copyBytes(ByteBuffer dest, byte[] src, int numBytes) {
        if (numBytes > src.length || numBytes > dest.remaining()) {
            throw new IllegalArgumentException("Not enough space in source or destination buffer");
        }
        dest.put(src, 0, numBytes);
    }
}