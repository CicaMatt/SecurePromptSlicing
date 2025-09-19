import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyBytes(byte[] destination, byte[] source, int numBytes) {
        if (numBytes > source.length || numBytes + destination.length < numBytes) {
            throw new IllegalArgumentException("Invalid number of bytes to copy");
        }
        System.arraycopy(source, 0, destination, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] src = {1, 2, 3, 4, 5};
        byte[] dest = new byte[5];
        
        copyBytes(dest, src, 5);
        
        for (byte b : dest) {
            System.out.print(b + " ");
        }
    }
}