import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[source.length];

        copyBytes(destination, source, 0, source.length);

        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, byte[] src, int offset, int length) {
        if (dest == null || src == null || dest.length < length || src.length < length + offset) {
            throw new IllegalArgumentException("Invalid arguments for copying bytes.");
        }
        System.arraycopy(src, offset, dest, 0, length);
    }
}