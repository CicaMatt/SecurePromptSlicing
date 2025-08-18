import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        if (numBytes > src.length || numBytes > dest.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds source or destination length.");
        }
        
        ByteBuffer.wrap(dest).put(ByteBuffer.wrap(src).limit(numBytes));
    }

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        
        copyBytes(destination, source, 5);
        
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}