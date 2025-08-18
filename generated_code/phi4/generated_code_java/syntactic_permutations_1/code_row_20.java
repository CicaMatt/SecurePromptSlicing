import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyBytes(byte[] destination, byte[] source, int length) {
        if (destination == null || source == null) {
            throw new IllegalArgumentException("Source or destination cannot be null");
        }
        
        if (length < 0 || length > Math.min(destination.length, source.length)) {
            throw new IllegalArgumentException("Invalid copy length");
        }

        System.arraycopy(source, 0, destination, 0, length);
    }

    public static void main(String[] args) {
        byte[] src = {1, 2, 3, 4, 5};
        byte[] dest = new byte[10];
        
        copyBytes(dest, src, 5);

        for (byte b : dest) {
            System.out.print(b + " ");
        }
    }
}