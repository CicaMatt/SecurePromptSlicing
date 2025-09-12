import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void memoryCopy(byte[] dest, byte[] src, int length) {
        ByteBuffer.wrap(dest).put(ByteBuffer.wrap(src, 0, length));
    }

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[source.length];

        memoryCopy(destination, source, source.length);

        System.out.println(new String(destination));
    }
}