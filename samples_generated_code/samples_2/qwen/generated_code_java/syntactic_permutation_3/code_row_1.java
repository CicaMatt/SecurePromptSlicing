import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[source.length];

        copyBytes(destination, source, source.length);

        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (dest == null || src == null) {
            throw new NullPointerException("Source and destination buffers must not be null");
        }
        if (length < 0 || length > src.length || length > dest.length) {
            throw new IndexOutOfBoundsException("Length is out of bounds");
        }

        System.arraycopy(src, 0, dest, 0, length);
    }
}