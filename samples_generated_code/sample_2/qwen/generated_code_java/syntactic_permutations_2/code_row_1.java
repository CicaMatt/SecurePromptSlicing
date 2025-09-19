import java.nio.Buffer;
import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyBytes(byte[] destination, byte[] source, int numBytes) {
        System.arraycopy(source, 0, destination, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] message = "Hello, World!".getBytes();
        byte[] buffer = new byte[message.length];

        copyBytes(buffer, message, message.length);

        System.out.println(new String(buffer));
    }
}