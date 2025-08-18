import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[source.length];
        int numberOfBytesToCopy = source.length;

        copyBytes(destination, source, numberOfBytesToCopy);

        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (dest == null || src == null || length <= 0 || length > src.length || length > dest.length) {
            throw new IllegalArgumentException("Invalid arguments for copying bytes");
        }
        System.arraycopy(src, 0, dest, 0, length);
    }
}