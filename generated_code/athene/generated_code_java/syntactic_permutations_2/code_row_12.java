import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void memcpy(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        String message = "Hello, World!";
        byte[] source = message.getBytes();
        byte[] buffer = new byte[source.length];

        memcpy(buffer, source, source.length);

        System.out.println(new String(buffer));
    }
}