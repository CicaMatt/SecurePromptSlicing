import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        
        copyBytes(destination, source, source.length);
        
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        if (dest == null || src == null) {
            throw new IllegalArgumentException("Source and Destination arrays cannot be null");
        }
        if (numBytes < 0 || numBytes > src.length || numBytes > dest.length) {
            throw new IndexOutOfBoundsException("Number of bytes to copy is out of bounds");
        }
        
        System.arraycopy(src, 0, dest, 0, numBytes);
    }
}