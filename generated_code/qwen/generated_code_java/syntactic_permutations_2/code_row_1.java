import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyBytes(byte[] destination, byte[] source, int numBytes) {
        if (numBytes > source.length || numBytes > destination.length) {
            throw new IllegalArgumentException("Number of bytes exceeds source or destination array length.");
        }
        System.arraycopy(source, 0, destination, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] message = "Hello, World!".getBytes();
        byte[] buffer = new byte[message.length];

        copyBytes(buffer, message, message.length);

        String copiedMessage = new String(buffer);
        System.out.println(copiedMessage);
    }
}