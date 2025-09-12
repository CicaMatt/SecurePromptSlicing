import java.nio.BufferUnderflowException;
import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void copyMemory(byte[] dest, int destOffset, byte[] src, int srcOffset, int length) {
        if (dest == null || src == null) {
            throw new NullPointerException("Source and destination arrays must not be null");
        }
        if (destOffset < 0 || srcOffset < 0 || length < 0 ||
            destOffset + length > dest.length || srcOffset + length > src.length) {
            throw new IndexOutOfBoundsException("Invalid offset or length specified");
        }

        System.arraycopy(src, srcOffset, dest, destOffset, length);
    }

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        copyMemory(destination, 0, source, 0, source.length);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}