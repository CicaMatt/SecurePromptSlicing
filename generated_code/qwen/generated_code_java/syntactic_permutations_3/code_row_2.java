import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] destination = new byte[5];
        byte[] source = "Hello".getBytes();

        copyBytes(destination, source, 5);

        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] destination, byte[] source, int numBytes) {
        if (numBytes > source.length || numBytes > destination.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds source or destination array length.");
        }
        System.arraycopy(source, 0, destination, 0, numBytes);
    }
}