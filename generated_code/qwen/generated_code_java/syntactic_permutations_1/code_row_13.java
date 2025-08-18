import java.nio.BufferUnderflowException;
import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyBytes(byte[] destination, byte[] source, int numBytes) {
        if (numBytes < 0 || numBytes > source.length || numBytes > destination.length) {
            throw new IllegalArgumentException("Invalid number of bytes to copy");
        }
        
        System.arraycopy(source, 0, destination, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        
        copyBytes(destination, source, 3);
        
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}