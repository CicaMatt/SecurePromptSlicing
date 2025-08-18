import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[source.length];

        copyBytes(destination, source, 3);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int numBytes) {
        if (numBytes > source.length || numBytes > destination.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds the length of source or destination array.");
        }
        System.arraycopy(source, 0, destination, 0, numBytes);
    }
}