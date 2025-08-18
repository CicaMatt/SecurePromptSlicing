import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyBytes(byte[] destination, byte[] source, int numberOfBytes) {
        if (numberOfBytes > source.length || numberOfBytes > destination.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds the length of source or destination array.");
        }
        System.arraycopy(source, 0, destination, 0, numberOfBytes);
    }

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        copyBytes(destination, source, 3);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}