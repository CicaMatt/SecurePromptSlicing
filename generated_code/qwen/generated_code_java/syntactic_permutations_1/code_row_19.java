import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void copyBytes(byte[] destination, byte[] source, int numBytes) {
        if (numBytes > source.length || numBytes > destination.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds source or destination array length.");
        }
        System.arraycopy(source, 0, destination, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        int numBytes = 3;

        copyBytes(destination, source, numBytes);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}