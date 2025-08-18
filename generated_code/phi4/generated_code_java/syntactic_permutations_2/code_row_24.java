import java.nio.ByteBuffer;

public class ByteCopier {

    public static void main(String[] args) {
        byte[] source = "This is a test message.".getBytes();
        byte[] destination = new byte[source.length];

        copyBytes(destination, source, source.length);

        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        if (dest == null || src == null) {
            throw new IllegalArgumentException("Source and destination must not be null.");
        }
        if (numBytes < 0 || numBytes > src.length || numBytes > dest.length) {
            throw new IllegalArgumentException("Number of bytes to copy is out of bounds.");
        }

        System.arraycopy(src, 0, dest, 0, numBytes);
    }
}