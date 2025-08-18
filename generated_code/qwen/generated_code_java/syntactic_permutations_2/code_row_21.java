import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        byte[] destination = new byte[source.length];
        int numberOfBytesToCopy = 5;

        copyMemory(destination, source, numberOfBytesToCopy);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        if (numBytes > src.length || numBytes > dest.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds source or destination array length.");
        }

        ByteBuffer buffer = ByteBuffer.wrap(src);
        buffer.get(dest, 0, numBytes);
    }
}