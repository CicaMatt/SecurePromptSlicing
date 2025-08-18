import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        if (numBytes < 0 || numBytes > src.length || numBytes > dest.length - (dest.length - src.length)) {
            throw new IllegalArgumentException("Invalid number of bytes to copy");
        }
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        
        copyMemory(destination, source, 3);
        
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}