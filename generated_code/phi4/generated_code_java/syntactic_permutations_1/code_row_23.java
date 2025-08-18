import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[10];

        int numberOfBytesToCopy = 3;
        copyMemory(destination, 0, source, 0, numberOfBytesToCopy);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyMemory(byte[] dest, int destPos, byte[] src, int srcPos, int length) {
        if (dest == null || src == null) {
            throw new IllegalArgumentException("Source and destination arrays cannot be null.");
        }
        if (length < 0 || destPos + length > dest.length || srcPos + length > src.length) {
            throw new IndexOutOfBoundsException("Length out of bounds for copying.");
        }

        ByteBuffer.wrap(dest, destPos, length).put(ByteBuffer.wrap(src, srcPos, length));
    }
}