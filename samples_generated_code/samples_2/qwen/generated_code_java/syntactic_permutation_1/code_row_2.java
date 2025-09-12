import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[source.length];
        int numBytesToCopy = 3;

        copyBytes(destination, source, numBytesToCopy);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (dest == null || src == null) {
            throw new IllegalArgumentException("Source and destination arrays must not be null");
        }
        if (length < 0 || length > src.length || length > dest.length) {
            throw new IndexOutOfBoundsException("Length is out of bounds");
        }

        System.arraycopy(src, 0, dest, 0, length);
    }
}