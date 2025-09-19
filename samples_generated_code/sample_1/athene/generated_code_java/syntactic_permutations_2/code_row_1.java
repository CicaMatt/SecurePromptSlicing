import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void memcpy(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        String message = "Hello, World!";
        byte[] source = message.getBytes();
        byte[] buffer = new byte[source.length];

        memcpy(buffer, source, source.length);

        String copiedMessage = new String(buffer);
        System.out.println(copiedMessage);
    }
}