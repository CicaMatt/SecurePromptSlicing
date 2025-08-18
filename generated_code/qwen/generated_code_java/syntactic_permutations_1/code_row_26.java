import java.nio.BufferUnderflowException;
import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyBytes(byte[] dest, int destPos, byte[] src, int srcPos, int length) {
        if (dest == null || src == null) {
            throw new NullPointerException("Source and destination buffers must not be null");
        }
        if (srcPos < 0 || destPos < 0 || length < 0 ||
            srcPos + length > src.length || destPos + length > dest.length) {
            throw new IndexOutOfBoundsException("Invalid source or destination position or length");
        }

        System.arraycopy(src, srcPos, dest, destPos, length);
    }

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        copyBytes(destination, 0, source, 0, source.length);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}