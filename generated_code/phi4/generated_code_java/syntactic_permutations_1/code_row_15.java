import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] src = {1, 2, 3, 4, 5};
        byte[] dest = new byte[10];

        // Copy 3 bytes from src to dest starting at index 0
        copyBytes(dest, 0, src, 0, 3);

        for (byte b : dest) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] destination, int destPos, byte[] source, int sourcePos, int length) {
        if (source == null || destination == null) {
            throw new IllegalArgumentException("Source and destination must not be null.");
        }
        if (length < 0) {
            throw new IllegalArgumentException("Length must be non-negative.");
        }

        int srcEnd = sourcePos + length;
        int destEnd = destPos + length;

        if (srcEnd > source.length || destEnd > destination.length) {
            throw new IndexOutOfBoundsException("Copy operation would exceed buffer bounds.");
        }

        System.arraycopy(source, sourcePos, destination, destPos, length);
    }
}