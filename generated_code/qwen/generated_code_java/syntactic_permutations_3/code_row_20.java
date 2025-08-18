import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[source.length];

        copyBytes(destination, source, source.length);

        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        System.arraycopy(src, 0, dest, 0, length);
    }
}